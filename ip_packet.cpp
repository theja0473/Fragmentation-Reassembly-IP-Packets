#include <iostream>
#include <cstdio>
#include "ip_packet.h"

IP_PKT makepacket(char msg[], int msglen){
	std::cout<<"Making Packet"<<std::endl;
	IP_PKT pckt;
	pckt.ip_verlen = 0x45;
	pckt.ip_len = msglen+20;
	pckt.ip_fragoff = 0;
	for(int i = 0; i<msglen; i++){
		pckt.ip_data[i] = msg[i];
	}
	return pckt;
}

IP_PKT copypacket(IP_PKT pckt1, int MTU){
	IP_PKT pckt;
	pckt.ip_verlen = pckt1.ip_verlen;
	pckt.ip_len = MTU;
	return pckt;
}

void display_content(IP_PKT pckt){
	int hlen = (pckt.ip_verlen & (0xf)) * 4;
	int data_len = pckt.ip_len - hlen;
	for(int i = 0; i<data_len; i++){
		std::cout<<pckt.ip_data[i];
	}
}