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

#include <map>
#include <string>
#include <iterator>
#include <iostream>

/*

syntax sendfile -r localhost:18000 -f testfile.txt
getopt
ststr - parse

*/


//variable declarations
char* ip;
char* filename;
unsigned short portnum = -1;
//struct hostent *hp; /* host information */ 
struct sockaddr_in servaddr; /* server address */
int sock;
struct sockaddr_in myaddr;
FILE *inputFile; /* File to send*/


//function declarations
void initConnection(int argc, char** argv);
void threadSend();
void printInputContents();
void handleOptions(int argc, char** argv);
int setupSocket();
int setupServerAddress();
int sendMessage(char *my_message, unsigned int messageLength);
int readfile(char *sendBuffer, unsigned int readSize);

int main(int argc, char** argv){
	//initialize the network connection
	initConnection(argc, argv);
	//send the file to the receiver
	threadSend();
	//closes the file after the file is sent
	fclose(inputFile);
	//terminate the program
	return 0;
}

void initConnection(int argc, char** argv){
	handleOptions(argc, argv);
	//print read contents
	printInputContents();
	//setup the socket
	if(setupSocket()==0){printf("ERROR SETTING UP SOCKET\n");exit (1);}
	//setup the server address
	if(setupServerAddress()==0){printf("ERROR SETTING UP ADDRESS\n");exit (1);}
}

void threadSend(){
	inputFile = fopen(filename,"r");
	if(inputFile==NULL){
		fputs ("File error",stderr);
		exit(1);
	}

	//obtain file size:
	fseek(inputFile,0,SEEK_END);
	unsigned int filesize = ftell(inputFile);
	rewind(inputFile);

	//send code
	

	
	
	int maxSendSize = 50000;
	int readSize=0;
	int readingPositionInTheInputFile=0;
	int bytesLeftToRead;
	bool finishedReading=false;
	while(!finishedReading){
		char *sendBuffer = (char*) malloc(50000); //make a buffer of .5 MB to send
		bytesLeftToRead= filesize - readingPositionInTheInputFile;
		if(bytesLeftToRead<maxSendSize){
			readSize=bytesLeftToRead;
			finishedReading=true;
		}
		else{
			readSize=maxSendSize;
			readingPositionInTheInputFile+=maxSendSize;
		}
		printf("readSize:\n",readSize);
		
		//Read the input file for 'readSize' amount of data and store it in sendBuffer
		if(readfile(sendBuffer,readSize)==0){printf("ERROR READING FILE\n");exit (1);}

		printf("sendBuffer[0]:%c\n",(char)sendBuffer[0]);

		//Send the contents of send buffer to the reciever
		if(sendMessage(sendBuffer,readSize)==0){printf("ERROR SENDING MESSAGE\n");exit (1);}
		
		free(sendBuffer);
	}
}

void handleOptions(int argc, char** argv){
	char* parseStr;
	char* IPAndPortnum;
	int option = 0;
	while ((option = getopt(argc,argv,"r:f:")) != -1){
		switch (option){
			case 'r': IPAndPortnum = optarg; 
				break;
			case 'f': filename = optarg;
				break;
			default: 
				exit(EXIT_FAILURE);
		}
	}
	parseStr=strtok(IPAndPortnum,":");
	//hostname=parseStr;
	//int *intIP = (int*) atoi(parseStr);
	//ip=(char*) malloc(sizeof intIP);
	//memcpy(ip, intIP, sizeof intIP);
	ip=parseStr;
	
	parseStr=strtok(NULL,":");
	portnum=atoi(parseStr);
	
}

int setupSocket(){
	//setting up the socket
	printf("setting up the socket\n");
	if( (sock=socket(AF_INET, SOCK_DGRAM,0)) < 0 ){
		perror("cannot create socket");
		printf("cannot create socket\n" );
		return 0;
	}
	memset((char *)&myaddr, 0, sizeof(myaddr));
	myaddr.sin_family=AF_INET;
	myaddr.sin_addr.s_addr = htonl(INADDR_ANY);
	myaddr.sin_port=htons(0);
	if (bind(sock, (struct sockaddr *)&myaddr, sizeof(myaddr)) < 0) { 
		perror("bind failed"); 
		printf("%s\n", "bind failed");
		return 0; 

	}
	return 1;
}

int setupServerAddress(){ 
	printf("setting up the server address\n");
	/* fill in the server's address and data */ 
	memset((char*)&servaddr, 0, sizeof(servaddr)); 
	servaddr.sin_family = AF_INET; 
	servaddr.sin_port = htons(portnum); 
	/* look up the address of the server given its name */ 
	//hp = gethostbyname(hostname);
	//hp=ip; 
	/*if (!hp) { 
		fprintf(stderr, "could not obtain address of %s\n", ip); 
		printf("could not obtain address of %s\n", ip);
		return 0; 
	} */
	/* put the host's address into the server address structure */ 
	//memcpy((void *)&servaddr.sin_addr, hp->h_addr_list[0], hp->h_length);
	if (inet_aton(ip, &servaddr.sin_addr)==0) {
		fprintf(stderr, "inet_aton() failed\n");
		exit(1);
	}

	//memcpy((void *)&servaddr.sin_addr, ip, sizeof ip);
	return 1;
}

int readfile(char *sendBuffer, unsigned int readSize){
	int readResult;
	unsigned int accu=0;
	while(accu<readSize){
		readResult = fread(sendBuffer+accu,1,readSize,inputFile);
		accu+=readResult;
		printf("readResult:%d, accu:%d, readSize:%d\n",readResult, accu,readSize);
	}
	if(readResult!=readSize){
		printf("ERROR READING FILE\n");
		return 0;
	}
	return 1;
}

int sendMessage(char *my_message, unsigned int messageLength){
	printf("sending message to %s\n", ip);
	/*unsigned int accu=0;
	unsigned int sendResult;
	while(accu<messageLength){
		sendResult = sendto(sock, my_message, strlen(my_message), 0, (struct sockaddr *)&servaddr, sizeof(servaddr));
		accu+=sendResult;
	}*/
	if (sendto(sock, my_message, strlen(my_message), 0, (struct sockaddr *)&servaddr, sizeof(servaddr)) < 0) { 
		perror("sendto failed"); 
		printf("sendto failed\n");
		return 0; 
	}
	return 1;
}

void printInputContents(){
	printf("\nprogram running, the following flags are read:\n");
	printf("filename:%s\n",filename);
	printf("portnum:%d\n",portnum);
	printf("ip:%s\n\n",ip);
}

