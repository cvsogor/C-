#include<iostream>
#include<fstream>
#include<math.h>
using namespace std;

typedef	unsigned long lon10; 
typedef	unsigned short int elem;

	class superLong{
bool b; 
lon10 i;
elem* p;
//---------
bool fl;
elem r0,r1,r2,lm,e;
lon10 l1,it,l;
elem* pn; 
public:
	superLong(){i=0;p=0;b=false;};
	superLong(lon10 ii){
		l=1;
      b=true;
      fl=false;
		i=ii;
		p=new elem[i];
		for(int k=0;k<i;k++){*(p+k)=0;};
	};
	superLong(superLong& m){b=false;i=m.i;p=m.p;};
	superLong& operator=(const superLong& m){b=false;i=m.i;p=m.p;return *this;};
	~superLong(){if ((p!=0)&(b))	delete[] p;	};
	elem& operator[](lon10 s){return *(p+s);};
	superLong& operator<<(ostream& o){
      for(int k=i-1;k>=0;k--){
      o.width(4);
		o.fill('0');
		o <<int(*(p+k))<<' ';};
      o<<'\n';
	return *this;};
   void flush(){fl=true;};
	superLong& operator*(const lon10 ll){
      if (!fl){
      if (ll<10000) {
         if (l<10000) {
            l*=ll;
         if (l<10000)  return *this;
         }; 
      } else l=ll;
     } else{l*=ll;};
      
      pn=new elem[i+3];   for(it=0;it<(i+3);it++){*(pn+it)=0;};   
   
   for(it=0;it<i;it++){    
   e=*(p+it);       
   lm=l%10000;
   l1=lm*e;
   r0=l1%10000;
   l1=(l/10000)*e+(l1/10000);
   r1=l1%10000;
   r2=l1/10000;
   
   lm=*(pn+it)+r0;
   *(pn+it)=lm%10000;
   lm=lm/10000;
   
   lm=*(pn+it+1)+r1+lm;
   *(pn+it+1)=lm%10000;
   lm=lm/10000;
   
   lm=*(pn+it+2)+r2+lm;
   *(pn+it+2)=lm%10000;
   *(pn+it+3)=lm/10000;

   };
   delete[] p;
   p=pn;
   if (i>5){
     if (*(p+i-3)>0) i+=3;
   } else i+=3;
l=1;
   return *this;         
	};
};
  superLong& fak(lon10 x){
static 	superLong m(1);
	m[0]=1;
   if (x<2) return m;
   for(lon10 i=2;i<x;i++){m*i;};
   if (x<10000) m.flush();
   return (m*x);
};
   
void main(){
	ofstream f("pr.txt");
   fak(10000)<<cout<<f;
} 