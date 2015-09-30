#include <iostream>
#include <vector>

#include "ip_packet.h"

using namespace std;

IP_PKT packet_unfragmented, reassembled_pkt;

vector <IP_PKT> fragmented;

void fragment(int MTU, IP_PKT pckt){
	if(pckt.ip_len<MTU) return;
	cout<<"Fragmentation starts "<<endl;
	int data_len = MTU - (pckt.ip_verlen & 0xf)*4;
	data_len = (data_len/8)*8;
	int totat_data_len = pckt.ip_len - (pckt.ip_verlen & 0xf)*4;
	int offset = 0;
	while(totat_data_len>0){
		IP_PKT fragment = copypacket(pckt,MTU);
		for(int i = 0; i<data_len; i++){
			fragment.ip_data[i] = pckt.ip_data[i+offset];
		}
		fragment.ip_fragoff = 0;
		if(totat_data_len>MTU) fragment.ip_fragoff = IP_MF;
		fragment.ip_fragoff += offset/8;
		offset += data_len;
		totat_data_len -= data_len;
		fragment.ip_len = data_len + 20;
		fragmented.push_back(fragment);
	}
	cout<<"Fragmentation ends "<<endl;
}

void display_framented_packets(vector <IP_PKT> pckts){
	int len = pckts.size();
	for(int i = 0; i<len; i++){
		cout<<"Frament "<<i+1<<" : ";
		display_content(pckts[i]);
		cout<<endl;
	}
}

void reassemble(vector <IP_PKT> pckts){
	int len = pckts.size();
	reassembled_pkt.ip_verlen = 0x45;
	reassembled_pkt.ip_fragoff = 0;
	int totat_data_len = 0;
	int current_data_len = 0;
	for(int i = 0; i<len; i++){
		current_data_len = pckts[i].ip_len - (pckts[i].ip_verlen & 0xf)*4;
		for(int j = 0; j<current_data_len; j++){
			reassembled_pkt.ip_data[totat_data_len+j] = pckts[i].ip_data[j];
		}
		totat_data_len += current_data_len;
	}
	reassembled_pkt.ip_len = totat_data_len + 20;
	cout<<"Reassembled packet is : ";
	display_content(reassembled_pkt);
	cout<<endl;
}

int main(){
	char msg[65536];
	int msglen;
	int MTU;
	cout<<"Enter the message length : ";
	cin>>msglen;
	cout<<"Enter the message : ";
	for(int i = 0; i<msglen; i++){
		cin>>msg[i];
	}
	cout<<"Enter the MTU for Fragmentation in bytes : ";
	cin>>MTU;
	packet_unfragmented = makepacket(msg,msglen);
	display_content(packet_unfragmented);
	fragment(MTU,packet_unfragmented);
	display_framented_packets(fragmented);
	reassemble(fragmented);
	return 0;
}