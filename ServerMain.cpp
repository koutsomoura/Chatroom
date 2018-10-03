#include <sys/types.h> /* See NOTES */
#include <sys/socket.h>
#include <unistd.h>
#include <netinet/in.h>
#include <iostream>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>
using namespace std;
#define maxmsg 500
#define maxLengthOfPendingConnections 10

void *myThreadFun(void *buf) 
{
	bzero((char*)buf,maxmsg);
	cin.getline((char*)buf,maxmsg);
	return NULL;
}
void Speak(int *acceptvalue){
	ssize_t	x;
	ssize_t y;
	pthread_t thread_1;

	char buf[maxmsg];

	do{
		pthread_create(&thread_1,NULL, myThreadFun, &buf); 
		//Wait until read buf from client
		x=read( *acceptvalue, buf, maxmsg);
		cout<<buf<<endl;
		//Clean buf
		bzero(buf,maxmsg);
		cin.getline(buf,maxmsg);
		//Send a new buf to client
		y=write( *acceptvalue,buf, maxmsg);
		pthread_join(thread_1, NULL); 
	//The loop stop only if read() return error
	}while (x!=-1);
	return;
}

int main(){
	int portno=5033;
	int socketfd=socket( AF_INET ,SOCK_STREAM ,0);

	struct sockaddr_in addr;
	struct sockaddr_in addr1;
	socklen_t clilen;

	bzero((char *) &addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(portno);
	//create a bind
	int desimo=bind(socketfd, (struct sockaddr *) &addr,sizeof(addr));
	//listen() marks the socket referred to by scketfd as passive socket
	int ginetePassive=listen(socketfd,maxLengthOfPendingConnections);
	//if listen return error
	if (ginetePassive!=0){
		cout<<"Lathos"<<endl;
	}

	clilen=sizeof(addr1);
	//Server accept connection
	int acceptvalue=accept(socketfd,(struct sockaddr *)&addr1,&clilen);
	//If accept() return error
	if (acceptvalue==-1){
		cout<<"Den ekane accept"<<endl;
	}

	Speak(&acceptvalue);
	
	close(acceptvalue);
	close(socketfd);
}