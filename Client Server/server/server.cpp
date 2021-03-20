#include <iostream>
#include <sys/socket.h>
#include <string>
#include <netinet/in.h>
#include <fcntl.h>
#include <unistd.h>
#include <list>
#include<utility>
#include<pthread.h>
using namespace std;
#define len 1000
#define CH_PORT 3425
typedef pair<string,int> par;

  list<par> lis;
  pthread_mutex_t mut=PTHREAD_MUTEX_INITIALIZER;
/*
volatile char semafor=0;
void setb(){
char c=1;
while(c){
asm_                   {
             mov al,1;
             xchg al,semafor;
             mov c,al; }
            }
};
void delb(){semafor=0;};
*/
void* newth(void* p);
int main()
{
    int sock, listener;
    struct sockaddr_in addr;
    char buf[len];
    int bytes_read;
    listener = socket(AF_INET, SOCK_STREAM, 0);
    if(listener < 0){perror("socket");exit(1);}
    addr.sin_family = AF_INET;
    addr.sin_port = htons(CH_PORT);
    addr.sin_addr.s_addr = htonl(INADDR_ANY);
    if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0) {perror("bind");exit(2);}
    listen(listener, 5);
    cout<<"server working...\n" ;
    while(1)
    {  
        void* p =new int(accept(listener, NULL, NULL));
        if(*((int*)p) < 0){perror("accept");exit(3);}
        pthread_t thread_id;
        pthread_create (&thread_id,NULL,&newth,p);
    }
return 0;
}
       
void* newth(void* p){
   int sock=*((int*)p);
   delete (int*)p;
   int i;
   bool za=true,zaza=false;
   char buf[len];
   list<par>::iterator a,b;
   string ss,s("enter name:\n"),ex("exit");

   while(za){
   za=false;
   send(sock,s.c_str(),s.length(),0);
   i=recv(sock,buf,len,0);
   if (zaza) i=recv(sock,buf,len,0);
   if (i>0) buf[i]=0 ;
                          else {goto exip;}
   s=buf;
   if (s==ex) {goto exip;}
   a=lis.begin();
   while(!(a==lis.end())){
      if ((a->first)==s) {za=true;zaza=true;s="this name is busy enter other:\n";}
      ++a;                  }
                }
   cout <<s<<" connected\n";
   a=lis.begin();
   while(!(a==lis.end())){
   if ((a->second)!=sock) {ss=s+" connected\n";send(a->second,ss.c_str(),ss.length(),0);
                                     ss=(a->first)+" in the chat\n"; send(sock,ss.c_str(),ss.length(),0);}
      ++a;                  }

   pthread_mutex_lock(&mut);
   lis.push_back(par(s,sock));
   pthread_mutex_unlock(&mut);

   fcntl(sock, F_SETFL, O_NONBLOCK);

   while(true){
   i=recv(sock,buf,len,0);
   if (i>0){
   buf[i]=0;
   if (buf==ex){goto exi;}
   a=lis.begin();
   while(!(a==lis.end())){if ((a->second)!=sock) {ss=s+": "+buf+'\n';send(a->second,ss.c_str(),ss.length(),0);}++a;}
             } else if (i==0) {
      exi:
         a=lis.begin();
         while(!(a==lis.end())){
         if ((a->second)!=sock) {ss=s+" exit\n";send(a->second,ss.c_str(),ss.length(),0);}
         else{b=a;}
         ++a;                      }
         cout<<s<<" exit\n";
         
         pthread_mutex_lock(&mut);
         lis.erase(b);
         pthread_mutex_unlock(&mut);
         
         goto exip;
                                  }

                   } ;
exip:
close(sock);
return 0;
}                      

