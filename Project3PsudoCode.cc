

//////////////////////////////
//		SENDFILE CODE		//
//////////////////////////////


int main(){
	threadSend();
	ThreadRecv();
	syncThreads();
	return 0;
}

windowStart=0;
windowSize=10;
map ackMap<unsigned int, char*>;
map dataMap;



void ThreadSend(){
	nextPacketToSend=0;
	//readingIndex=0;
	while(!finishedReading){

		while(ackMap[windowStart]==NULL){
			//sendPackets inside the window
			if(nextPacketToSend<(windowStart+windowSize)){
				if(ackMap[nextPacketToSend]==NULL){
					send(encode(dataMap[nextPacketToSend]));
				}
				nextPacketToSend++;
			}
			else{
				nextPacketToSend=windowStart;
				if(ackMap[nextPacketToSend]==NULL){
					send(encode(dataMap[nextPacketToSend]));
				}
				nextPacketToSend++;
			}
		}
		ackMap.remove[windowStart]
		dataMap.remove[windowStart]
		windowStart++;
	}
}

void ThreadRecv(){
	while(!finishedRecieving){  //check for window start
		recvFrom;
		if(checksum(packet)){
			ackMap.add(packet);
		}
	}
}

//////////////////////////////
//		RECVFILE CODE		//
//////////////////////////////

unsigned int NextPacketToWriteToFile;
map dataMap;
filename = NULL;
bool doneReceiving=false;

int main(){
	
	NextPacketToWriteToFile=1; //because the first (Seq# 0) packet is the filename
	
	//start the recv and write threads
	std::thread recv(threadRecvAndAck);
	std::thread write(threadWritefile);
	//sync recv and write threads
	recv.join();
	write.join();

	//terminte the program
	return 0;
}

void threadRecvAndAck(){
	while(!doneReceiving){
		recvAndAck();
	}
}

void recvAndAck(){
	char *packet = recvFrom();
	if(checksum(packet)){
		if(FILENAME){
			//make a new file
		}
		else if(DATA or FILE_END){
			//add packet to map
		}
		else {
			//ERROR: file corruption not detected by checksum.
			//		The header might be corrupted
		}
		send(ack);
	}
}

void threadWritefile(){
	while(!doneReceiving){
		if(filename!=NULL){
			writefile();
		}
	}
}

void writefile(){
	char* nextPacket = dataMap[NextPacketToWriteToFile];
	if(nextPacket!=NULL){
		if(nextPacket[0]==DATA){
			//write packet to file
			map.remove(packet);
		}
		else if(nextPacket[0]==FILE_END){
			//close the file
			doneReceiving=true;
			map.remove(packet);
		}
		else{
			//ERROR, INAPPROPRIATE PACKETS ARE STORED IN THE DATA MAP
		}
		NextPacketToWriteToFile++;
	}
}


