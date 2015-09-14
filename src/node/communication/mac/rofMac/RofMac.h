#ifndef _ROFMAC_H_
#define _ROFMAC_H_

#include <omnetpp.h>
#include "VirtualMac.h"
#include "VirtualMobilityManager.h"
#include "RofPacket_m.h"
#include <math.h>

using namespace std;

//all nodes have same communication radius
const int COMMUNICATION_RADIUS = 20;
const double INITIAL_ENERGY = 18720;

//Sink is fixed
const int SINK_NODE = 0;

//all nodes will be assigned exclusive ID starting with
int packetID = 101;

const double T_WAIT = 0.06;	//ms
const double T_WINDOW = 0.01; //ms
const int CW = 6; //6 CONTENT WINDOW slots each of 10ms each
const double ALPHA = 0.75;
//must maintain the relationship : lambda1 + lambda2 = 1;
const double LAMBDA1 = 0.2;
const double LAMBDA2 = 0.8;
//mainatain T_wait = T_window*CW

//flag to tell if overstepping mode is on
bool overstepping_mode = 0;

enum PacketType {
	BUSY_PACKET = 0,
	ATF_PACKET = 1,
	DATA_PACKET = 2
};

enum timers{
	SEND_ATF = 0,
	OVERSTEPPING_MODE = 1
};

enum channel{
	DATA_CHANNEL = 0,
	BUSY_CHANNEL = 2
};
class RofMac: public VirtualMac
{
	/* In order to create a MAC based on VirtualMacModule, we need to define only two
	 * functions: one to handle a packet received from the layer above (routing),
	 * and one to handle a packet from the layer below (radio)
	 */
	protected:
		void fromRadioLayer(cPacket *, double, double);
		void fromNetworkLayer(cPacket *, int);
		void getCurrentLocation(double&,double&);
		void findNodeLocation(double& x, double& y, int node);
		double computeDistance(double& x1, double& y1, double& x2, double& y2);
		void sendATF(int sendTo);
		void timerFiredCallback(int);
		void sendPacket(RofPacket *packet);
		void sendBusyPacket();
		void forwardPacket();
		double max(double, double);
		double getEnergyConsumed();
		void startup();
		//variables for storing node's location
		double x, y;
		bool ATFsent=0;
		int sender_address;
		//bool sendATF=1;
};

#endif
