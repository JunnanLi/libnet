#include "nmac.h"

void l2_learn(){
	printf("===l2 learn====\n");

	
	union nmacH_macP nm;

	recv_packet(&(nm.nmac_h), "(ip proto 253) && (src host 192.168.40.147)");
	
	printf("index_mac_header: %d\n", &(nm.nmac_h));	
	printf("index_mac_port: %d\n",&(nm.mac_p));
	printf("port: %d\n",nm.mac_p.port);
	printf("mac: %02x:%02x:%02x:%02x:%02x:%02x\n",nm.mac_p.mac[0],nm.mac_p.mac[1],nm.mac_p.mac[2],nm.mac_p.mac[3],nm.mac_p.mac[4],nm.mac_p.mac[5]);
	
}


void rule_manage(){
	
	printf("===xterm2\n");
}
