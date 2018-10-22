#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <thread>
#include <signal.h>
using namespace std;
#define maxmsg 500
bool contision=true;
//Create a String with max letters maxmsg
char buf[maxmsg];

void HandlerSingal(int s){
	printf("\nQUIT BB\n");
	contision=false;
}

void *myThreadFun(void *mpla) 
{
	while(1){
		//Input String from keyboard
		cin.getline(buf,maxmsg);
		//Send the String to the Server via value mpla
		write( *(int *)mpla,buf, maxmsg);
		//Eliminate the String
		bzero(buf,maxmsg);
	}
}
void *myThreadFun2(void *mpla) 
{
	while(1){
		//Receive a message from Server
		read( *(int *)mpla,buf, maxmsg);
		//Print the massage 
		cout<<buf<<endl;
		//Eliminate the String
		bzero(buf,maxmsg);
	}
}

void Comm(int *socketfd){
	pthread_t thread_1;
	pthread_t thread_2;
	//Create thread_1
	pthread_create(&thread_1,NULL, myThreadFun, (void *) &(*(int *)socketfd) );
	//Create thread_2
	pthread_create(&thread_2,NULL, myThreadFun2, (void *) &(*(int *)socketfd) ); 

	while(contision){
		sleep(1);
	}

}

int main(){
	int portno=5033;
	int socketfd=socket( AF_INET ,SOCK_STREAM ,0);
	signal (SIGINT, HandlerSingal);

	struct sockaddr_in addr1;
	memset((char *) &addr1,0, sizeof(addr1));

	addr1.sin_family=AF_INET;
	addr1.sin_port=htons(portno);
	addr1.sin_addr.s_addr=inet_addr("127.0.0.1");
	socklen_t clilen;
	clilen=sizeof(addr1);

	//Connect Client with Server
	int connectvalue=connect(socketfd,(struct sockaddr *)&addr1,clilen);
	//If connect() return error
	if (connectvalue!=0){cout <<"No connection... "<<endl;}

	Comm( &socketfd);

	close(connectvalue);
	close(socketfd);

}