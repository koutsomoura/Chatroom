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



int main(){
	int portno=5033;
	int socketfd=socket( AF_INET ,SOCK_STREAM ,0);
	ssize_t	x;
	ssize_t y;
	pthread_t threads;
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
	int ginetePassive=listen(socketfd,10);
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
	char buf[500];


	do{
		//Wait until read buf from client
		x=read( acceptvalue, buf, 500);
		cout<<buf<<endl;
		//Clean buf
		bzero(buf,500);
		cin.getline(buf,500);
		//Send a new buf to client
		y=write( acceptvalue,buf, 500);
	//The loop stop only if read() return error
	}while (x!=-1);

	close(acceptvalue);
	close(socketfd);
}