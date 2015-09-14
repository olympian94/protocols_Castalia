cplusplus {{
	#include "MacPacket_m.h"
}}
class MacPacket;
packet RofPacket extends MacPacket {
	//sender adds location information in its packets
	double senderX;
	double senderY;
	int senderID;
	//sender can send data, ATF or busy packet
	int packetType;
	//eacch node is assigned unique ID
	int packetID;
	//where the packet is supposed to go
	int sinkAddress;
}