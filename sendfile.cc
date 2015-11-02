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
struct hostent *hp; /* host information */ 
struct sockaddr_in servaddr; /* server address */
int sock;
struct sockaddr_in myaddr;

//function declarations
void printInputContents();
void handleOptions(int argc, char** argv);
int setupSocket();
int setupServerAddress();


int main(int argc, char** argv){
	handleOptions(argc, argv);

	//struct hostent *host = gethostbyname(argv[1]);
  	//server_addr = *(unsigned int *) host->h_addr_list[0];

	printInputContents();

	//setup the socket
	if(setupSocket()==0){return 0;}
	//setup the server address
	if(setupServerAddress()==0){return 0;}


	char *my_messsage = "this is a test message"; 
	/* send a message to the server */ 
	if (sendto(fd, my_message, strlen(my_message), 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) { 
		perror("sendto failed"); 
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

int setupSocket(){
	//setting up the socket
	if( (sock=socket(AF_INET, SOCK_DGRAM,0)) < 0 ){
		perror("cannot create socket");
		return 0;
	}
	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family=AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port=htons(0);
	if (bind(sock, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) { 
		perror("bind failed"); return 0; 
	}
}

int setupServerAddress(){ 
	
	/* fill in the server's address and data */ 
	memset((char*)&servaddr, 0, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(portnum); 
	/* look up the address of the server given its name */ 
	hp = gethostbyname(hostname); 
	if (!hp) { 
		fprintf(stderr, "could not obtain address of %s\n", host); 
		return 0; 
	} 
	/* put the host's address into the server address structure */ 
	memcpy((void *)&servaddr.sin_addr, hp->h_addr_list[0], hp->h_length);

}

void printInputContents(){
	printf("program running, the following flags are read:\n");
	printf("filename:%s\n",filename);
	printf("portnum:%d\n",portnum);
	printf("hostname:%s\n",hostname);
}