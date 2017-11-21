#include "nmac.h"

void add_flow(u32 addr, u32 *data, int numData){
	int i=0;
	struct nmac_header *nmac_h;
	struct nmac_header *nmac_h_recv;
	nmac_h = (struct nmac_header *)malloc(sizeof(struct nmac_header));
	nmac_h_recv = (struct nmac_header *)malloc(sizeof(struct nmac_header));
	nmac_h->opt = 1;
	nmac_h->id = 0;
	nmac_h->pad =0;
	for(i=0; i<numData; i++){
		nmac_h->id++;
		nmac_h->addr = addr;
		nmac_h->data = data[i];
	
		send_packet(nmac_h);
		recv_packet(nmac_h_recv,"(ip proto 253) && (dst net 192.111.40.147)");
		printf("nmac respond id: %d\n",nmac_h_recv->id);

		addr++;
	}
}

void read_flow(u32 addr, u32 *data, int numData){
	int i=0;
	struct nmac_header *nmac_h;
	struct nmac_header *nmac_h_recv;
	nmac_h = (struct nmac_header *)malloc(sizeof(struct nmac_header));
	nmac_h_recv = (struct nmac_header *)malloc(sizeof(struct nmac_header));
	nmac_h->opt = 2;
	nmac_h->id = 0;
	nmac_h->pad =0;
	for(i=0; i<numData; i++){
		nmac_h->id++;
		nmac_h->addr = addr;
		nmac_h->data = 0;
	
		send_packet(nmac_h);
		recv_packet(nmac_h_recv,"(ip proto 253) && (dst net 192.111.40.147)");
		
		data[i] = nmac_h_recv->data;
	
		addr++;
	}
	
}
