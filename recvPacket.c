#include "nmac.h" 


void recv_packet(struct nmac_header *nmac_h, char * bpf_string)
{  
    pcap_t * pcap_h = NULL;  
    char error_content[100] = "";
    const unsigned char *packet = NULL;
    char *p_net_interface_name = NULL;
    struct pcap_pkthdr p_pkthdr;
  
    p_net_interface_name = pcap_lookupdev(error_content);  
    if(NULL == p_net_interface_name)  
    {  
        perror("pcap_lookupdev");  
        exit(-1);  
    }     
    //p_net_interface_name ="eth0";
 
    pcap_h = pcap_open_live(p_net_interface_name,BUFSIZE,0,0,error_content);
    if(pcap_h == NULL){
        printf("error_pcap_handle\n");
        exit(0);
    }

	//BPF filter;
	struct bpf_program filter;
	pcap_compile(pcap_h, &filter, bpf_string, 1, 0);
	//"dst port 8080", 1, 0);
	//and dst net 192.168.40.147
	//ip proto 253
	pcap_setfilter(pcap_h, &filter);

	// pcap packet;
	packet = pcap_next(pcap_h,&p_pkthdr);
	if(packet == NULL){
		perror("pcap_next");
		exit(-1);
	}
  

	unsigned char *mac_string;
    	struct nmac_header *nmac_h2;
	struct ip_header * ip_h;
	struct ether_header *eth_h;
    u8 protocol;
    printf("----------------------------------------------------\n");
    printf("%s\n", ctime((time_t *)&(p_pkthdr.ts.tv_sec))); 
	printf("len: %d,caplen: %d\n", p_pkthdr.len, p_pkthdr.caplen);
    
	eth_h = (struct ether_header *) packet;
	ip_h = (struct ip_header *) (packet +14);
	nmac_h2 = (struct nmac_header *) (packet +34);
/*      
    mac_string = (unsigned char *) nmacPkt->eth_h.ether_smac;
    printf("Mac Source Address is %02x:%02x:%02x:%02x:%02x:%02x\n",*(mac_string+0),*(mac_string+1),*(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));  
    mac_string = (unsigned char *) nmacPkt->eth_h.ether_dmac;
    printf("Mac Destination Address is %02x:%02x:%02x:%02x:%02x:%02x\n",*(mac_string+0),*(mac_string+1),*(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));  
*/      

/*
    protocol = nmacPkt->ip_h.protocol;
    printf("ip protocol is :%02x\n",protocol);

	printf("src ip is :%d.%d.%d.%d\n", nmacPkt->ip_h.srcIP[0],nmacPkt->ip_h.srcIP[1],nmacPkt->ip_h.srcIP[2],nmacPkt->ip_h.srcIP[3]);
	printf("dst ip is :%d.%d.%d.%d\n", nmacPkt->ip_h.dstIP[0],nmacPkt->ip_h.dstIP[1],nmacPkt->ip_h.dstIP[2],nmacPkt->ip_h.dstIP[3]);
*/

	printf("=====recv info====\n");

for(int i=0;i<46;i++)
{
printf("%02x", packet[i]);
if(i%16 ==15 ) printf("\n");
}
printf("\n");

	printf("nmac id :%d\n", nmac_h2->id);
	printf("nmac opt :%d\n", nmac_h2->opt);
	printf("nmac addr :%d\n", nmac_h2->addr);
	printf("nmac data :%d\n", nmac_h2->data);

	
	nmac_h->id = nmac_h2->id;
	nmac_h->opt = nmac_h2->opt;
	nmac_h->pad = nmac_h2->pad;
	nmac_h->addr = nmac_h2->addr;
	nmac_h->data = nmac_h2->data;
	
	
    pcap_close(pcap_h);
	
} 
