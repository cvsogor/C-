#include <iostream>
#include <string>
#include <list>
#include <algorithm>
#include<utility>

using namespace std;


#pragma comment (lib,"wsock32.lib")
#include <winsock.h>
#pragma comment (lib,"kernel32.lib")
#include <process.h>

const int CHAT_PORT = 32000;
typedef pair<string,int> par;
typedef len 1000;
list<par> li;

unsigned long _stdcall newconnection(void* p){//копируется ли каждый раз в другое место?
   int sock=*((int*)p);
   delete p;
   int i;
   bool za=true;
   unsigned long nonbl;
   char buf[len];
   list<par>::iterator a,b;
   string ss,s("enter name:\n"),ex("exit");

   while(za){
   za=false;
   send(sock,s.c_str(),s.length(),0);
   i=recv(sock,buf,len,0);
   if (i>0) buf[i]=0;//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
   s=buf;

   a=li.begin();
   while(!(a==li.end())){
      if ((a->first)==s) {za=true;s="this name is busy enter other:\n";}
      ++a;   }

   }
   cout <<s<<" connected\n";
   a=li.begin();
   while(!(a==li.end())){
   if ((a->second)!=sock) {ss=s+" connected\n";send(a->second,ss.c_str(),ss.length(),0);}
      ++a;
   }

   //-------------------------
   li.push_back(par(s,sock));
   //-------------------------
   nonbl=1;
   ioctlsocket(sock,FIONBIO,&nonbl);

   while(true)
   {

   i=recv(sock,buf,len,0);
   if (i>0){
   buf[i]=0;
   if (buf==ex){goto exi;}
   a=li.begin();
   while(!(a==li.end())){if ((a->second)!=sock) {ss=s+": "+buf+'\n';send(a->second,ss.c_str(),ss.length(),0);}++a;}
            }
     else if (i==0) {
      exi:
         a=li.begin();
         while(!(a==li.end())){
         if ((a->second)!=sock) {ss=s+" exit\n";send(a->second,ss.c_str(),ss.length(),0);}
         else{b=a;}
         ++a;}
         cout<<s<<" exit\n";
         li.erase(b);
         return 0;
                     }

   }

   closesocket(sock);
   return 0;
};
void main()
{
   WSADATA wsadata;
   WSAStartup(0x101,&wsadata);
   int sock=socket(AF_INET,SOCK_STREAM,0);


   if (!sock) {cout<<"error: can't create socket...\n";exit(1);}
   sockaddr_in saddr;//структура
   saddr.sin_family=AF_INET;//протокол
   saddr.sin_addr.s_addr = 0;//IP сервера,для сервера 0  
   saddr.sin_port=htons(CHAT_PORT);//установить порт
   //инициализируем сокет для сервака(прослушивание)
   if (bind(sock,(sockaddr *) &saddr,sizeof(sockaddr))) {cout<<"error: can't bind\n";exit(1);}
   cout<<"server have started.\n";
   listen(sock,50);//перевод в состояние прослушивания(50 клиентов максимум в очереди одновременно)
   
   while(true){
   void* p=new int(accept(sock,0,0));
   CreateThread(NULL,8192/*размер стека*/,newconnection,p,0,0);
      };
   
   
   closesocket(sock);
   WSACleanup();
}

