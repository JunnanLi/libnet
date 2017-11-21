#include "nmac.h" 


void send_packet(struct nmac_header *nmac_h)
{  
	char *send_payload;	

        char err_buf[100] = "";  
        libnet_t *lib_net = NULL;  
        int lens = 0;  
        libnet_ptag_t lib_t = 0;  
        unsigned char src_mac[6] = {0x00,0x0c,0x29,0x97,0xc7,0xc1};
        unsigned char dst_mac[6] = {0x73,0x27,0xea,0xb5,0xff,0xd8};
        char *src_ip_str = "192.168.40.147";
        char *dst_ip_str = "192.111.40.147";
        unsigned long src_ip,dst_ip = 0;  
      
        lens = sizeof(struct nmac_header);  
      
        lib_net = libnet_init(LIBNET_LINK_ADV, "ens33", err_buf);
        if(NULL == lib_net)  
        {  
            perror("libnet_init");  
            exit(-1);  
        }  
      
        src_ip = libnet_name2addr4(lib_net,src_ip_str,LIBNET_RESOLVE);
        dst_ip = libnet_name2addr4(lib_net,dst_ip_str,LIBNET_RESOLVE);   
      

	send_payload = (char *)nmac_h;

	printf("====send info====\n");
	printf("nmac id :%d\n", nmac_h->id);
	printf("nmac opt :%d\n", nmac_h->opt);
	printf("nmac addr :%d\n", nmac_h->addr);
	printf("nmac data :%d\n", nmac_h->data);

        lib_t = libnet_build_ipv4(
                                    20+lens,  
                                    0,  
                                    500,  
                                    0,  
                                    10,  
                                    253,  
                                    0,  
                                    src_ip,  
                                    dst_ip,  
                                    send_payload,  
                                    lens,  
                                    lib_net,  
                                    0  
                                );  
      
        lib_t = libnet_build_ethernet(
                                        (u_int8_t *)dst_mac,  
                                        (u_int8_t *)src_mac,  
                                        0x800,
                                        NULL,  
                                        0,  
                                        lib_net,  
                                        0  
                                    );  
        int res = 0;  
        res = libnet_write(lib_net);
        if(-1 == res)  
        {  
            perror("libnet_write");  
            exit(-1);  
        }  
      
        libnet_destroy(lib_net);
          
        printf("----ok-----\n");
} 
