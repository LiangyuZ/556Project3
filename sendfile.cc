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
void printInputContents();
void handleOptions(int argc, char** argv);


int main(int argc, char** argv){
	handleOptions(argc, argv);
	printInputContents();

	int sock;
	if( (sock=socket(AF_INET, SOCK_DGRAM,0)) < 0 ){
		perror("cannot create socket");
		return 0;
	}

	return 1;
}

void handleOptions(int argc, char** argv){
	char* parseStr;
	char* hostnameAndPortnum;
	int option = 0;
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
	parseStr=strtok(hostnameAndPortnum,":");
	hostname=parseStr;
	parseStr=strtok(NULL,":");
	portnum=atoi(parseStr);
	
}

void printInputContents(){
	printf("program running, the following flags are read:\n");
	printf("filename:%s\n",filename);
	printf("portnum:%d\n",portnum);
	printf("hostname:%s\n",hostname);
}