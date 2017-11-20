#include <stdio.h> 
#include <pcap.h> 
#include <arpa/inet.h> 
#include <time.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h> 
//#include <libnet.h> 

#define BUFSIZE 1514 

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;


struct ether_header {
    unsigned char ether_dmac[6];  
    unsigned char ether_smac[6]; 
    unsigned short ether_type; 
};

struct ip_header {
    u8 ihl_version;
    u8 tos;
    u16 len;
    u16 id;
    u16 offset;
    u8 ttl;
    u8 protocol;
    u16 checkSum;
    u32 srcIP;
    u32 dstIP;
};

struct nmac_header{
    u8 opt;
    u32 data;
};

struct nmac_packet{
    struct ether_header eth_h;
    struct ip_header ip_h;
    struct nmac_header nmac_h;
};





  

void get_packet(unsigned char *argument, const struct pcap_pkthdr *packet_heaher, const unsigned char *packet_content)  
{  
    unsigned char *mac_string;
    struct nmac_packet *nmacPkt;
    u8 protocol;
    printf("----------------------------------------------------\n");
    printf("%s\n", ctime((time_t *)&(packet_heaher->ts.tv_sec))); 
    nmacPkt = (struct nmac_packet *) packet_content;
      
    mac_string = (unsigned char *) nmacPkt->eth_h.ether_smac;
    printf("Mac Source Address is %02x:%02x:%02x:%02x:%02x:%02x\n",*(mac_string+0),*(mac_string+1),*(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));  
    mac_string = (unsigned char *) nmacPkt->eth_h.ether_dmac;
    printf("Mac Destination Address is %02x:%02x:%02x:%02x:%02x:%02x\n",*(mac_string+0),*(mac_string+1),*(mac_string+2),*(mac_string+3),*(mac_string+4),*(mac_string+5));  
      
    protocol = nmacPkt->ip_h.protocol;
    printf("Ethernet type is :%02x\n",protocol);  
    
    usleep(800*1000);  
}  


int main(int argc, char *argv[])  
{  
    pcap_t * pcap_handle = NULL;  
    char error_content[100] = "";   // 出错信息  
    const unsigned char *p_packet_content = NULL;       // 保存接收到的数据包的起始地址  
    unsigned char *p_mac_string = NULL;         // 保存mac的地址，临时变量  
    unsigned short ethernet_type = 0;           // 以太网类型  
    char *p_net_interface_name = NULL;      // 接口名字  
    struct pcap_pkthdr protocol_header;  
    //struct ether_header *ethernet_protocol;  
  
    //获得接口名  
    p_net_interface_name = pcap_lookupdev(error_content);  
    if(NULL == p_net_interface_name)  
    {  
        perror("pcap_lookupdev");  
        exit(-1);  
    }     
   
    //p_net_interface_name ="eth0";

    //打开网络接口  
    pcap_handle = pcap_open_live(p_net_interface_name,BUFSIZE,0,0,error_content);

    if(pcap_handle == NULL){
        printf("error_pcap_handle\n");
        exit(0);
    }

    printf("ljn-2====\n");
    printf("capture a Packet from p_net_interface_name :%s\n",p_net_interface_name);  


if(pcap_loop(pcap_handle,-1,get_packet,NULL) < 0)  
    {  
        perror("pcap_loop");  
    }  

      
    pcap_close(pcap_handle);  
    return 0;  
}  