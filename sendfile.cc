#include "sendfile.h"

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>


/*

syntax sendfile -r localhost:18000 -f testfile.txt
getopt
ststr - parse

*/


//variable declarations
char* hostname;
char* filename;
int portnum = -1;

//function declarations
void printHostName();
void handleOptions(int argc, char** argv);


int main(int argc, char** argv){
	//printf("the program seems to be working \n");
	int option = 0;
	char* hostnameAndPortnum;
	char* parseStr;
	

	int sock;

	
	printf("program running, the following flags are read:\n");
	//printf("r:%s\n",hostnameAndPortnum);
	printf("filename:%s\n",filename);


	parseStr=strtok(hostnameAndPortnum,":");
	hostname=parseStr;
	//printf("parsed values:\n");
	printHostName();
	parseStr=strtok(NULL,":");
	portnum=atoi(parseStr);
	printf("portnum:%d\n",portnum);


	if( (sock=socket(AF_INET, SOCK_DGRAM,0)) < 0 ){
		perror("cannot create socket");
		return 0;
	}




	return 1;
}

void handleOptions(int argc, char** argv){
	while ((option = getopt(argc,argv,"r:f:")) != -1){
		switch (option){
			case 'r': hostnameAndPortnum = optarg; 
				break;
			case 'f': filename = optarg;
				break;
			default: 
				exit(EXIT_FAILURE);
		}
	}

	
}

void printHostName(){
	printf("hostname:%s\n",hostname);
}