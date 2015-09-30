#ifndef IP_PACKET

#define IP_PACKET

typedef int IPaddr;

#define MAX_IP_PAYLOAD 2048 /*artificial:toavoidimpl.varsizepkts*/

typedef struct ip{
	char ip_verlen;	/*IP version and header length:*/
	char ip_tos; 		/*type of service:*/
	short ip_len;		/*total packet length(inoctets)*/
	short ip_id;		/*datagram id:*/
	short ip_fragoff;	/*fragment offset(in 8 octets) + flags:*/
	char ip_ttl;		/*time to live in gateway hops:*/
	char ip_proto;	/*IP protocol:*/
	short ip_chksum;	/*header checksum:*/
	IPaddr ip_src;		/*IP address of source:*/
	IPaddr ip_dst;		/*IP address of destination:*/
	char ip_data[MAX_IP_PAYLOAD];		/*variable length data:*/
}IP_PKT;

#define DATASIZE 1024

#define IP_PKT_SIZE sizeof(N_PDU_TYPE)

#define IP_MF 0x2000			/*more fragments bitmask(8192inbase10)*/
#define IP_DF 0x4000			/*don't fragment bit:*/
#define IP_FRAGOFF 0x1fff		/*frag offsetmask: masks out the top-3 bits of a 16-bithhhhhshort'*/
#define IPMHLEN 20				/*min(standard) IP header length(inbytes)*/

IP_PKT makepacket(char msg[], int msglen);

IP_PKT copypacket(IP_PKT pckt1, int MTU);

void display_content(IP_PKT pckt);

#endif