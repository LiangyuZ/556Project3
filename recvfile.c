
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

void HandlePacket();
int main(int argc, char** argv) {
  printf("in main\n");
  //####get input recv port
  char *recvPort = NULL;
  int c;
  while ((c = getopt (argc, argv, "p:")) != -1)
    switch (c)
      {
      case 'p':
        recvPort = optarg;
        break;
      default:
        abort ();
	  }
	// printf("recvPort: %s\n",recvPort);
  
  //####wait to receive
  int recvSize;
  // allocate a memory buffer in the heap
  char *buf = (char *)malloc(1000000);	//1MB size
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

  /* set option so we can reuse the port number quickly after a restart */
  //SO_REUSEADDR: allows the port number to be reused without timing out.
  int optval = 1;
  if (setsockopt (sock, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof (optval)) <0)
    {
      perror ("setting TCP socket option");
      abort ();
    }	
	
  //setup source address
  struct sockaddr_in sin;
  /* fill in the address of the server socket */
  memset (&sin, 0, sizeof (sin));
  sin.sin_family = AF_INET;
  sin.sin_addr.s_addr = INADDR_ANY;
  sin.sin_port = htons (*(unsigned short *)recvPort); 
  printf("htons: %d\n",htons (*(unsigned short *)recvPort));
  /* bind server socket to the address */
  if (bind(sock, (struct sockaddr *) &sin, sizeof (sin)) < 0)
    {
      perror("binding socket to address");
      abort();
    }  
	
  while(1){
	  //TODO
	  recvSize = recvfrom(sock, buf, 1000000, 0, (struct sockaddr *) &sin, sizeof (sin) );
	  if(recvSize  >  0){
		HandlePacket();
	  }
	  // else if(recvSize<0){
		  
	  // }
	  
  }
  
  
  return 0;
}

  //handle the received packet
  void HandlePacket(){}