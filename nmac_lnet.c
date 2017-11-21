#include "nmac.h"

int main(int argc, char *argv[]){
	

	struct nmac_header *nmac_h;
	struct nmac_header *nmac_h_recv;

	nmac_h = (struct nmac_header *)malloc(sizeof(struct nmac_header));
	nmac_h_recv = (struct nmac_header *)malloc(sizeof(struct nmac_header));


	while(1){
/*
		recv_packet(nmac_h_recv, "(ip proto 253) && (dst net 192.111.40.147)");
		printf("request id:%d\n",nmac_h_recv->id);	

		nmac_h->id = nmac_h_recv->id;
		nmac_h->opt = 3;
		nmac_h->pad = 0;
		nmac_h->addr = nmac_h_recv->addr;
		nmac_h->data = nmac_h_recv->data;
		sleep(1);
*/

		nmac_h->id = 1;
		nmac_h->opt = 1;
		nmac_h->pad = 2;
		nmac_h->addr = 3;
		nmac_h->data = 0;
		
		int a;	
		printf("input a number\n");
		scanf("%d",&a);
		send_packet(nmac_h);

	}
	return 0;  
} 
