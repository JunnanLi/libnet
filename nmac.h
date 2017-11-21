#include <stdio.h> 
#include <pcap.h> 
#include <arpa/inet.h> 
#include <time.h> 
#include <stdlib.h> 
#include <string.h> 
#include <unistd.h>
#include <libnet.h>
#include <pthread.h>


#define BUFSIZE 1514 

typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned int u32;


struct ether_header {
    u8 ether_dmac[6];  
    u8 ether_smac[6]; 
    u16 ether_type; 
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
    u8 srcIP[4];
    u8 dstIP[4];
};

struct nmac_header{
	u8 id;
	u8 opt;
	u16 pad;
	u32 addr;
	u32 data;
};

struct nmac_packet{
    struct ether_header eth_h;
    struct ip_header ip_h;
    struct nmac_header nmac_h;
};

struct mac_port{
	u8 port;
	u8 mac[6];
	u8 pad[5];
};

union nmacH_macP{
	struct mac_port mac_p;
	struct nmac_header nmac_h;
};


void recv_packet(struct nmac_header *nmac_h, char * bpf_string);

void send_packet(struct nmac_header *nmac_h);

void add_flow(u32 addr, u32 *data, int numData);

void read_flow(u32 addr, u32 *data, int numData);

void l2_learn();

void rule_manage();

