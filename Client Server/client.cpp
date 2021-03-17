#include<iostream>
#include<string>
using namespace std;
#include<conio.h>
#include <winsock.h>
#pragma comment (lib,"wsock32.lib")
#define len 1000
class client{
int SERVER_PORT;
char* SERVER_NAME;
sockaddr_in saddr;
int sock,i;
unsigned long nonbl;
char buf[len];
public:
client(char* ip,int port){
	SERVER_PORT = port;
	SERVER_NAME=ip;	
   WSADATA wsadata;
   WSAStartup(0x101,&wsadata);
   sock=socket(AF_INET,SOCK_STREAM,0);
   if (!sock) {cout<<"error: can't create socket...\n";cin.get();exit(1);}
   saddr.sin_family=AF_INET;
   saddr.sin_addr.s_addr = inet_addr(SERVER_NAME);
   saddr.sin_port=htons(SERVER_PORT);
   if(connect(sock,(sockaddr *)&saddr,sizeof(sockaddr))) {cout<<"error: server not answered\n";cin.get();exit(1);}
   nonbl=1;
   ioctlsocket(sock,FIONBIO,&nonbl);         
};
void operator<<(string& s){send(sock,s.c_str(),s.size(),0);};
void get_mess(){
   i=0;
   while(i!=-1){
   i=recv(sock,(char *) &buf,len,0);
   if (i!=-1) {buf[i]=0;cout << buf;if(i==0){cout<<"server failed!!!";cin.get();exit(1);};}
   }
};
~client(){
	closesocket(sock);
	WSACleanup();};
};
void main(){
	string s,ex("exit");
   client cl("127.0.0.1",32000);
	while(s!=ex){
   if ((kbhit()==1)&&(getch()==13)) {cout<<"enter message:";cin>>s;cl<<s;};
   cl.get_mess();
   }
} 


