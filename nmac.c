#include "nmac.h"

int main(int argc, char *argv[]){
	
	pthread_t pid_l2,pid_rule;
	int ret;
	ret = pthread_create(&pid_l2, NULL, (void *)l2_learn, NULL);
	if(ret <0){
		printf("pthread create error\n");
		exit(0);	
	}
	
	ret = pthread_create(&pid_rule, NULL, (void *)rule_manage, NULL);
	if(ret <0){
		printf("pthread create error_rule_manage\n");
		exit(0);
	}

	u32 addr = 10;
	u32 data[2];
	data[0] = 100;
	data[1] = 101;

	//add_flow(addr, data, 2);

	//read_flow(addr, data, 2);

	pthread_join(pid_l2, NULL);
	pthread_join(pid_rule, NULL);

	return 0;  
} 
