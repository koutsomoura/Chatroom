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
	cout<<socketfd<<endl;
	pthread_t threads;
	struct sockaddr_in addr;
	
	bzero((char *) &addr, sizeof(addr));
	addr.sin_family = AF_INET;
	addr.sin_addr.s_addr = INADDR_ANY;
	addr.sin_port = htons(portno);


	//addr.sin_family=AF_INET;
	//addr.sin_port=htons(portno);
	//addr.sin_addr.s_addr=INADDR_ANY;
	
	int desimo=bind(socketfd, (struct sockaddr *) &addr,sizeof(addr));
	//bind(socketfd,( sockaddr *)&addr,sizeof(addr));


	cout<<"prin to listen()"<<desimo<<endl; 

	int ginetePassive=listen(socketfd,10);
		cout<<"meta to listen()"<<ginetePassive<<endl; 

	if (ginetePassive!=0){cout<<"Lathos"<<endl;}
	struct sockaddr_in addr1;
	socklen_t clilen;
	clilen=sizeof(addr1);
	int acceptvalue=accept(socketfd,(struct sockaddr *)&addr1,&clilen);
	if (acceptvalue==-1){cout<<"Den ekane accept"<<endl;}
	cout<<"perase to accept"<<endl; 
	char buf[500];

ssize_t	x;
	do{
	x=read( acceptvalue, buf, 500);
	cout<<buf<<endl;

	bzero(buf,500);
	cin.getline(buf,500);

	ssize_t y=write( acceptvalue,buf, 500);
}while (x!=-1);

	close(acceptvalue);
	close(socketfd);
}