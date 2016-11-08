/**
		\file		:	arp_fill.c
		\author		:	Sreeram Sadasivam
		\brief		:	ARP table filling up and clearing.	
*/

#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<omp.h>
#include "convenience_methods.h"

void pingSystemCallWithAddress(char ipaddr[]) {

	char pingCmd[200];
	strcpy(pingCmd,"ping -w 5 ");
	strcat(pingCmd,ipaddr);
	strcat(pingCmd," &");
	system(pingCmd);
}

void clearARPSystemCallWithAddress(char ipaddr[]) {

	char clearARPCacheCmd[200];
	strcpy(clearARPCacheCmd,"sudo arp -d ");
	strcat(clearARPCacheCmd,ipaddr);
	system(clearARPCacheCmd);
}

void clearARPCache(char gateway_ip_addr[],char my_ip_addr[]) {

	char resString[200],finalString[200];
	int index;
	splitStringWithSplitWordAndPosition(resString,gateway_ip_addr,".",3);
	printf("Clearing ARP Cache...\n");


	for(index=100;index<=150;index++) {

		sprintf(finalString,"%s.%d",resString,index);
		if(strcmp(finalString,my_ip_addr)!=0) {
			clearARPSystemCallWithAddress(finalString);
		}
	}


}

void arpTableFillUpWithGatewayIPAndMyIP(char gateway_ip_addr[],char my_ip_addr[]) {

	char resString[200],finalString[200];
	int index;
	splitStringWithSplitWordAndPosition(resString,gateway_ip_addr,".",3);
	printf("Filling up the ARP Table...\n");

	#pragma omp parallel for private(finalString,resString,my_ip_addr,index)
	for(index=100;index<=150;index++) {

		sprintf(finalString,"%s.%d",resString,index);
		if(strcmp(finalString,my_ip_addr)!=0) {
			pingSystemCallWithAddress(finalString);
		}
	}
}

main(int argc,char *argv[]) {

	if(argc>=3) {
		if(strcmp(argv[argc-3],"-f")==0) {
			arpTableFillUpWithGatewayIPAndMyIP(argv[argc-2],argv[argc-1]);
		}
		else if(strcmp(argv[argc-3],"-c")==0){
			clearARPCache(argv[argc-2],argv[argc-1]);
		}
		else {
			printf("Invalid Option...\n");
		}
	}
}