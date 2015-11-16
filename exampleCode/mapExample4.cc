#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>

#include <map>
#include <string>
#include <iterator>
#include <iostream>
#include <memory>

struct packet{
	char* buffer;
	int size;
};
 typedef struct packet PACKET;

//FUNCTION DECLARATIONS
//void displayMap(std::map<unsigned int, PACKET> map, const char* name);



//MAIN CODE
int main(){
	std::shared_ptr<PACKET> packet (new PACKET());

	packet->buffer = (char*) "First Message";
	packet->size = sizeof(packet->buffer);

	std::map<unsigned int, std::shared_ptr<PACKET>> mapOfMessages;
	mapOfMessages.insert(std::make_pair(1, packet));
	printf("added the following message to the map:\n");
	printf("%s\n", mapOfMessages[1]->buffer); 
	printf("size:%d\n", mapOfMessages[1]->size);
	
	mapOfMessages.erase(1);

	return 0;
}

