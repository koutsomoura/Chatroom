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


int main(){
	int portno=5033;
ssize_t x;
	int socketfd=socket( AF_INET ,SOCK_STREAM ,0);

	struct sockaddr_in addr1;
	memset((char *) &addr1,0, sizeof(addr1));

	addr1.sin_family=AF_INET;
	addr1.sin_port=htons(portno);
	addr1.sin_addr.s_addr=inet_addr("127.0.0.1");
	socklen_t clilen;
	clilen=sizeof(addr1);
		cout<<"prin to connect()"<<endl; 


	int connectvalue=connect(socketfd,(struct sockaddr *)&addr1,clilen);
			cout<<"meta to connect()"<<connectvalue<<endl; 

	if (connectvalue!=0){cout <<"Parta "<<endl;}
	char buf[500];
	while(connectvalue==0){
		cin.getline(buf,500);

		ssize_t y= write( socketfd,buf, 500);
		bzero(buf,500);

		x=read( socketfd,buf, 500);
		cout<<buf<<endl;
	}

	close(socketfd);

}