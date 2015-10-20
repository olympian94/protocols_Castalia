#include "RofMac.h"

Define_Module(RofMac);


/*
	Add node no of contention winner to Busy packet.
	No duplication and mobility.
*/
void RofMac::startup()
{
//	trace()<<"Setting channel";
//	toRadioLayer(createRadioCommand(SET_CARRIER_FREQ, ((DATA_CHANNEL-10)*5) + 2400) );	
//	toRadioLayer(createRadioCommand(SET_STATE, RX));
}

void RofMac::fromNetworkLayer(cPacket * pkt, int destination)
{
	RofPacket* rofpacket = new RofPacket("Data Packet", MAC_LAYER_PACKET);
	getCurrentLocation(x, y);
	rofpacket->setSenderX(x);
	rofpacket->setSenderY(y);
	rofpacket->setPacketID(packetID);
	rofpacket->setPacketType(DATA_PACKET);
	rofpacket->setSinkAddress(SINK_NODE);
	rofpacket->setSenderID(SELF_MAC_ADDRESS);
	rofpacket->setDestination(BROADCAST_MAC_ADDRESS);

	//for current simulation only NODE 1 is the sender and NODE 0 is the intended final Receiver
	//broadcast to neighbours
	if(SELF_MAC_ADDRESS==1)
	{
		trace() << "**broadcasting new " <<packetID;
		packetID++;
		setTimer(OVERSTEPPING_MODE,T_WAIT);
		//set to DATA CHANNEL, send DATA PACKET
		//toRadioLayer(createRadioCommand(SET_CARRIER_FREQ, ((DATA_CHANNEL-10)*5) + 2400) );
		sendPacket(rofpacket);
		//change state to RX, listen for ATF packet which is recieved in DATA CHANNEL only
		//toRadioLayer(createRadioCommand(SET_STATE, RX));
	}
	else
		delete (rofpacket);
}

void RofMac::fromRadioLayer(cPacket * pkt, double rssi, double lqi)
{
	RofPacket *recievedPacket = dynamic_cast <RofPacket*>(pkt);
	if(recievedPacket->getPacketType() == DATA_PACKET) 
	{
		if(SELF_MAC_ADDRESS == recievedPacket->getSinkAddress())
		{
			//packet has reached sink
			trace()<<"**Packet "<<recievedPacket->getPacketID()<<" reached destination";
			sendBusyPacket(0);
		}
		else
		{
			//set payload
			data=recievedPacket->getPacketID();
			//get coordinates of sink
			double currentNode_Xcoordinate, currentNode_Ycoordinate;
			double sinkX, sinkY;
			double sender_Xcoordinate = recievedPacket->getSenderX();
			double sender_Ycoordinate = recievedPacket->getSenderY();
			double nodePriority;

			getCurrentLocation(currentNode_Xcoordinate,currentNode_Ycoordinate);
			findNodeLocation(sinkX,sinkY,SINK_NODE);
			//distance b/w sender and sink
			double d = computeDistance(sender_Xcoordinate, sender_Ycoordinate, sinkX, sinkY);
			//distance b/w node and sink
			double di = computeDistance(currentNode_Xcoordinate, currentNode_Ycoordinate, sinkX, sinkY);
			//distance b/w node and sender
			double ri = computeDistance(currentNode_Xcoordinate, currentNode_Ycoordinate, sender_Xcoordinate, sender_Ycoordinate);
			if(!overstepping_mode)
			{
				if( (d-di)>0)
				{
					double residual_energy= INITIAL_ENERGY - getEnergyConsumed();
					trace()<<"**Residual Energy= "<<residual_energy;
					nodePriority = ( (d-di) * ri * residual_energy ) / ( COMMUNICATION_RADIUS*COMMUNICATION_RADIUS*INITIAL_ENERGY );
				}
				else
					//when d-di<0 and its not overstepping mode, this node should drop the packet, hence set nodePriority to -1
					nodePriority = -1;
			}
			else if(overstepping_mode)
			{
				nodePriority = max( ( LAMBDA1*(d-di)/COMMUNICATION_RADIUS ) + ( LAMBDA2*ri/COMMUNICATION_RADIUS ) , 0);
			}

			if(nodePriority>=0)
			{
				//calculate probability of sending in kth window
				double max_pr_window=0.0, temp, pr_window, probability_array[CW];
				int k, j, window;

				//calculate probability for each window k, k=0...CW-1
				for(k=0; k<CW; k++)
				{
					temp = 1+(1-nodePriority)*ALPHA;
					pr_window = nodePriority*pow(temp,k);	//its 'k-1' in formula when k starts with 1, here k starts with 0
					if(pr_window>1)
						pr_window=1;
					probability_array[k]=pr_window;
				}

				//find slot number 'window' in T_WAIT which has maximum probability
				for(j=0; j<CW; j++)
				{
					if(probability_array[j]>max_pr_window)
					{
						max_pr_window=probability_array[j];
						window = j;
					}
				}
				if(max_pr_window==0)
					//if pr = 0, send in last window ie. CW-1, after that anyway OVERSTEPPING MODE will start
					window = CW-1;
				
				trace()<<"**(Node Priority, window, current Node ID) = "<<nodePriority<<" , "<<window<<" , "<<SELF_MAC_ADDRESS;

				//set the variable 'sender_address', it is to this address that ATF will be sent
				sender_address = recievedPacket->getSenderID();
				
				//send ATF after waiting for 'window' time
				ATFsent=0;
				//set timer. After timer expires ATF will be sent
				srand (SELF_MAC_ADDRESS);
				float random_wait=(rand()%10)/(float)1000+SELF_MAC_ADDRESS/(float)10000;

				setTimer(SEND_ATF, window*T_WINDOW+random_wait);
				trace()<<"**timer set, time = "<<window*T_WINDOW+random_wait<<endl;
				//meanwhile set channel to BUSY CHANNEL so that node can listen for BUSY TONE
				//toRadioLayer(createRadioCommand(SET_CARRIER_FREQ, ((BUSY_CHANNEL-10)*5) + 2400) );
			}
			else
			{
				//discard packet because d-di<0
				trace()<<"**Discarding packet because d-di<0";
			}
		}
	}

	else if(recievedPacket->getPacketType() == ATF_PACKET && recievedPacket->getDestination() == SELF_MAC_ADDRESS) 
	{	
		//the sender has recieved ATF from one of the recievers. Now send Busy Tone on channel 2 to suppress
		//other nodes' activity.
		trace()<<"**Recieved ATF from "<<recievedPacket->getSenderID()<<", sending busy...";
		//ATFrecieved=1;
		//cancel the timer which was set to begin OVERSTEPPING_MODE
		overstepping_mode = 0;
		cancelTimer(OVERSTEPPING_MODE);
		//set to BUSY CHANNEL, send data
		//toRadioLayer(createRadioCommand(SET_CARRIER_FREQ, ((BUSY_CHANNEL-10)*5) + 2400) );
		sendBusyPacket(recievedPacket->getSenderID());
	} 
	else if(recievedPacket->getPacketType() == BUSY_PACKET) 
	{
		//means that some other reciever has already sent ATF to sender
		//This node is now supposed to drop the packet.
		if(recievedPacket->getSinkAddress() == SELF_MAC_ADDRESS && ATFsent)
		{
			//recieved busy tone from sender, confirmation to forward Packet
			trace()<<"**Recieved BUSY packet, Forwarding Packet "<<data<<" ATFsent = "<<ATFsent;
			//change channel to data channel and send 
			//toRadioLayer(createRadioCommand(SET_CARRIER_FREQ, ((DATA_CHANNEL-10)*5) + 2400) );
			forwardPacket();
			//setTimer(OVERSTEPPING_MODE,T_WAIT);
			//reset variable
			ATFsent=0;
			//Now listen for the next data packet
			//toRadioLayer(createRadioCommand(SET_STATE, RX));
		}
		else if(!ATFsent || recievedPacket->getSinkAddress() == 0)
		{
			//This node has not sent ATF and it has recieved BUSY from sender hence it should drop its packet
			trace()<<"**Recieved BUSY packet, cancelling SEND ATF timer. ATFsent = "<<ATFsent;
			//cancel the timer which was set to send ATF
			cancelTimer(SEND_ATF);
			//change back to data channel to listen for next data packet
			//toRadioLayer(createRadioCommand(SET_CARRIER_FREQ, ((DATA_CHANNEL-10)*5) + 2400) );
			//radio stays in RX mode
		}
	}

	//this block is not required, its just for debugging purposes
	else if(recievedPacket->getPacketType() == ATF_PACKET && recievedPacket->getDestination() != SELF_MAC_ADDRESS) 
	{
		//If recieved packet is ATF but this node is not the intended reciever, then do nothing
		//trace()<<"**Received ATF not meant for me";
	}
	
}

void RofMac::getCurrentLocation(double& x, double& y) {

	VirtualMobilityManager *nodeMobilityModule = check_and_cast<VirtualMobilityManager*>(getParentModule()->getParentModule()->getParentModule()->getSubmodule("node",SELF_MAC_ADDRESS)->getSubmodule("MobilityManager"));
	x = nodeMobilityModule->getLocation().x;
	y = nodeMobilityModule->getLocation().y;

}

void RofMac::findNodeLocation(double& x, double& y, int i) {
	VirtualMobilityManager *nodeMobilityModule = check_and_cast<VirtualMobilityManager*>(getParentModule()->getParentModule()->getParentModule()->getSubmodule("node",i)->getSubmodule("MobilityManager"));
	x = nodeMobilityModule->getLocation().x;
	y = nodeMobilityModule->getLocation().y;
}

double RofMac::computeDistance(double& x1, double& y1, double& x2, double& y2) {
	return sqrt((x1-x2)*(x1-x2)+(y1-y2)*(y1-y2));
}

void RofMac::sendPacket(RofPacket *packet) {
	packet->setSource(SELF_MAC_ADDRESS);
	toRadioLayer(packet);
	toRadioLayer(createRadioCommand(SET_STATE, TX));
}


void RofMac::sendATF(int sendTo) {
	RofPacket* atfpacket = new RofPacket("ATF Packet", MAC_LAYER_PACKET);
	//trace()<<"In sendATF setting to Data Channel";
	//toRadioLayer(createRadioCommand(SET_CARRIER_FREQ, ((DATA_CHANNEL-10)*5) + 2400) );
	atfpacket->setDestination(sendTo);
	atfpacket->setPacketType(ATF_PACKET);
	atfpacket->setSenderID(SELF_MAC_ADDRESS);
	sendPacket(atfpacket);
	//set flag for checking the flow 
	ATFsent=1;
	trace()<<"**ATFSent";
}

void RofMac::sendBusyPacket(int contentionWinner) {
	RofPacket* busypacket = new RofPacket("BUSY Packet", MAC_LAYER_PACKET);
	trace() << "**Broadcasting Busy";
	busypacket->setDestination(BROADCAST_MAC_ADDRESS);
	busypacket->setPacketType(BUSY_PACKET);
	busypacket->setSinkAddress(contentionWinner);
	sendPacket(busypacket);
}

void RofMac::timerFiredCallback(int timer) {
	trace()<<"**Timer called : "<<timer;
	switch(timer)
	{
		case SEND_ATF :
		//protocol says: before sending ATF, check BUSY CHANNEL to see if busy tone is heard. That is handled because after the timer
		//is set for sending ATF, the channel is changed to BUSY CHANNEL
		//If the node had recieved busy tone, this timer would have been cancelled by code and execution would never reach this block
		
		//Change channel to data channel and send ATF
		//toRadioLayer(createRadioCommand(SET_CARRIER_FREQ, ((DATA_CHANNEL-10)*5) + 2400) );
		srand (time(NULL));
	 	printf ("(%lf)\n", (rand()%10)/(float)1000);

		sendATF(sender_address);
		//after sending ATF , change channel to BUSY CHANNEL and listen for busy packet from sender
		//toRadioLayer(createRadioCommand(SET_CARRIER_FREQ, ((BUSY_CHANNEL-10)*5) + 2400) );
		//toRadioLayer(createRadioCommand(SET_STATE, RX));
		break;

		case OVERSTEPPING_MODE :
		//overstepping mode
		trace()<<"**Beginning Overstepping mode...";
		overstepping_mode = 1;
		forwardPacket();
		break;
		default:	trace()<<"**Default case in timerFiredCallback";
	}
}

void RofMac::forwardPacket() {
	RofPacket* newPacket = new RofPacket("Data Packet", MAC_LAYER_PACKET);
	getCurrentLocation(x, y);
	newPacket->setSenderX(x);
	newPacket->setSenderY(y);
	newPacket->setPacketID(data);
	newPacket->setPacketType(DATA_PACKET);
	newPacket->setSinkAddress(SINK_NODE);
	newPacket->setSenderID(SELF_MAC_ADDRESS);
	newPacket->setDestination(BROADCAST_MAC_ADDRESS);
	sendPacket(newPacket);
}

double RofMac::max(double a, double b) {
		if(a>b)
			return a;
		return b;
}

double RofMac::getEnergyConsumed() {
	ResourceManager *nodeResModule = check_and_cast<ResourceManager*>(getParentModule()->getParentModule()->getParentModule()->getSubmodule("node",SELF_MAC_ADDRESS)->getSubmodule("ResourceManager"));
	return nodeResModule->getSpentEnergy( );
}