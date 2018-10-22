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
#include <signal.h>
bool contision=true;
//Create a String with max letters maxmsg
char buf[maxmsg];

void HandlerSingal(int s){
	printf("\nQUIT BB\n");
	contision=false;
}
void *myThreadFun(void *mpla) 
{
	while(contision){
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
	while(contision){
		//Receive a message from Server
		read( *(int *)mpla,buf, maxmsg);
		//Print the massage 
		cout<<buf<<endl;
		//Eliminate the String
		bzero(buf,maxmsg);
	}	
}
void Speak(int *acceptvalue){

	pthread_t thread_1;
	pthread_t thread_2;
	//Create thread_1
	pthread_create(&thread_1,NULL, myThreadFun,(void *) &(*(int *)acceptvalue)); 
	//Create thread_2
	pthread_create(&thread_2,NULL, myThreadFun2,(void *) &(*(int *)acceptvalue)); 

	while(contision){
		sleep(1);
	}
}

int main(){
	int portno=5033;
	int socketfd=socket( AF_INET ,SOCK_STREAM ,0);

	struct sockaddr_in addr;
	struct sockaddr_in addr1;
	socklen_t clilen;
	signal (SIGINT, HandlerSingal);

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
   	close(ginetePassive);
   	close(desimo);
	close(socketfd);
}