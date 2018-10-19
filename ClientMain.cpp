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

void HandlerSingal(int s){
	printf("QUIT BB\n");
}

void *myThreadFun(void *mpla) 
{
	char buf[maxmsg];
	char quitbuton[]="q";

	cin.getline(buf,maxmsg);
	if (strcmp(buf,quitbuton)==0){
			raise(SIGTERM);
			pid_t  pid;
			kill(pid,SIGKILL);
	}

		//Send buf to server
	write( *(int *)mpla,buf, maxmsg);

	bzero(buf,maxmsg);
	sleep(1);
	return NULL;
}

void Comm(int *socketfd){
	ssize_t x;
	ssize_t y;
	pthread_t thread_1;

	//create string with 500 max letters
	char buf[maxmsg];
	do{

		pthread_create(&thread_1,NULL, myThreadFun, (void *) &(*(int *)socketfd) ); 
		sleep(1);
		read( *socketfd,buf, maxmsg);
		cout<<buf<<endl;

		//Clean buf
		bzero(buf,maxmsg);

	//The loop stop only if read() return error
	}while (x!=-1);
	return;

}

int main(){
	int portno=5033;
	int socketfd=socket( AF_INET ,SOCK_STREAM ,0);
	signal (SIGTERM, HandlerSingal);

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

	close(connectvalue);
	close(socketfd);

}