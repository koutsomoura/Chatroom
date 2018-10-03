#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include <arpa/inet.h>
#include <thread>
using namespace std;
#define maxmsg 500

void *myThreadFun(void *buf) 
{
	bzero((char*)buf,maxmsg);
	cin.getline((char*)buf,maxmsg);
	return NULL;
}

void Comm(int *socketfd){
	ssize_t x;
	ssize_t y;
	pthread_t thread_1;

	//create string with 500 max letters
	char buf[maxmsg];

	do{

		pthread_create(&thread_1,NULL, myThreadFun, &buf); 
		cin.getline(buf,maxmsg);
		//Send buf to server
		y= write( *socketfd,buf, maxmsg);
		//Clean buf
		bzero(buf,maxmsg);
		//Recieve buf from server
		x=read( *socketfd,buf, maxmsg);
		pthread_join(thread_1, NULL); 
		cout<<buf<<endl;

	//The loop stop only if read() return error
	}while (x!=-1);
	return;

}

int main(){
	int portno=5033;
	int socketfd=socket( AF_INET ,SOCK_STREAM ,0);

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
	if (connectvalue!=0){cout <<"Parta "<<endl;}

	Comm( &socketfd);

	close(socketfd);

}