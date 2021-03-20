#include <iostream>
#include <string>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <fcntl.h>
using namespace std;

#define len 1000
#define CH_PORT 3425

class client{
	int sock,i,i2;
	struct sockaddr_in addr;
	int SERVER_PORT;
    char buf[len];
public:
client(int port){
    SERVER_PORT = port;
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if(sock < 0)
    {
        perror("socket");
        exit(1);
    }
    addr.sin_family = AF_INET;
    addr.sin_port = htons(SERVER_PORT);
    addr.sin_addr.s_addr =htonl(INADDR_LOOPBACK); //htonl(0x7f000001);
    if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    {   perror("connect");
        exit(2);    }
    i=recv(sock,buf,len,0);
    if (i>0) {buf[i]=0;cout << buf<<"\n";}else{exit(1);};
    fcntl(sock, F_SETFL, O_NONBLOCK);
        };
void operator<<(string& s){send(sock,s.c_str(),s.size(),0);};
void get_mess(){
    i=0;
    while(i!=-1){
    i=recv(sock,buf,len,0);
    if (i>-1) {if(i==0){cout<<"server failed!!!";cin.get();exit(1);};buf[i]=0;cout << buf<<"\n";}
       }
};
~client(){close(sock);};
};

int main(){
	string s,ex("exit");
	client cl(CH_PORT);
	while(s!=ex){
    cout<<"enter message:";cin>>s;cl<<s;
    cl.get_mess();
			}
    return 0;
}                         
