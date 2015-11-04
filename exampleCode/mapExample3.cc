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

//FUNCTION DECLARATIONS
void displayMap(std::map<unsigned int, char*> map, const char* name);

//MAIN CODE
int main(){

	std::map<unsigned int, char*> mapOfMessages;
	char *firstMessage = (char*) "First Message";
	mapOfMessages.insert(std::make_pair(1, firstMessage));
	displayMap(mapOfMessages, "mapOfMessages");
	firstMessage = (char*) "New Message";
	mapOfMessages.insert(std::make_pair(2, firstMessage));
	displayMap(mapOfMessages, "mapOfMessages");

	mapOfMessages.insert(std::make_pair(3, firstMessage));
	mapOfMessages.insert(std::make_pair(4, firstMessage));
	mapOfMessages.insert(std::make_pair(5, firstMessage));
	mapOfMessages.insert(std::make_pair(6, firstMessage));
	mapOfMessages.insert(std::make_pair(7, firstMessage));
	mapOfMessages.insert(std::make_pair(8, firstMessage));
	mapOfMessages.insert(std::make_pair(9, firstMessage));

	displayMap(mapOfMessages,"mapOfMessages");

	mapOfMessages.erase(1);
	displayMap(mapOfMessages,"mapOfMessages");
	
	

	return 0;
}


void displayMap(std::map<unsigned int, char*> map, const char *name){
	typedef std::map<unsigned int, char*>::iterator it_type;
	printf("\n%s={\n", name);
	int numCol=4;//numbers of entry in each row.
	int count=0;
	for(it_type iterator = map.begin(); iterator != map.end(); iterator++) {
    // iterator->first = key
    // iterator->second = value
		if(count % numCol==0){printf("  ");}
		printf("(%d,%s) ", iterator->first, iterator->second);
		if(count % numCol ==numCol-1){printf("\n");}

		count++;
	}
	printf("\n}\n");
}
