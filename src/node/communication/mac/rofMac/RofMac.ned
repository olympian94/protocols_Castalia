package node.communication.mac.rofMac;

simple RofMac like node.communication.mac.iMac {
	parameters:
		bool collectTraceInfo = default(false);
		int macMaxPacketSize = default(0);
		int macBufferSize = default(16);
		int macPacketOverhead = default(8);
	gates:
		output toNetworkModule;
		output toRadioModule;
		input fromNetworkModule;
		input fromRadioModule;
		input fromCommModuleResourceMgr;
}
