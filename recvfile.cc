
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
#include <iostream>

void handle_packet();
void get_port(int argc, char** argv, unsigned short recvPort);
int main(int argc, char** argv) {
  printf("in main\n");
  //####get input recv port
  unsigned short recvPort;
  get_port(argc,argv,recvPort);
  
  //####initialization
  int recvSize;
  // allocate a memory buffer in the heap
  unsigned int buf_size = 100000;
  char *buf = (char *)malloc(buf_size);	//1MB size
  if (!buf)
    {
      perror("failed to allocated buffer");
      abort();
    }

  // create a socket
  int sock;	//our recv socket
  if ((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
    {
      perror ("opening TCP socket");
      abort ();
    }
	
  //setup source address
  struct sockaddr_in srcAddr;
  /* fill in the address of the server socket */
  memset (&srcAddr, 0, sizeof (srcAddr));
  srcAddr.sin_family = AF_INET;
  srcAddr.sin_addr.s_addr = INADDR_ANY;
  srcAddr.sin_port = htons (recvPort); 
  printf("htons: %d\n",htons (recvPort));
  /* bind server socket to the address */
  if (bind(sock, (struct sockaddr *) &srcAddr, sizeof (srcAddr)) < 0)
    {
      perror("binding socket to address");
      abort();
    }  
	
  //####wait to receive
  
  while(1){
	  printf("in while \n");
	  sockaddr_in recv_addr;
	  socklen_t addrlen = sizeof(recv_addr);
	  printf("in while 2\n");
	  recvSize=recvfrom(sock, buf, buf_size, 0, (struct sockaddr *) &recv_addr, &addrlen);
	  printf("in while 3\n");
	  if(recvSize<= 0 ){
		  perror("Receive error\n");
		  return 0;
	  }
	  
	  //####check completeness
	  
	  
	  //####send back ACK
	  
	  
  }
  
  
  return 0;
}

  //handle the received packet
  void handle_packet(){}
  
  void get_port(int argc, char** argv, unsigned short recvPort){	  
	  int c;
	  while ((c = getopt (argc, argv, "p:")) != -1)
		switch (c)
		  {
		  case 'p':
			recvPort =atoi(optarg);
			break;
		  default:
			abort ();
		  }  
		printf("recvPort: %d\n",recvPort);
  }