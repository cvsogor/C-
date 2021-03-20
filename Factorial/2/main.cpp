#include<iostream>
#include<fstream>
using namespace std;
typedef unsigned long intr;
typedef unsigned short int into;
class vect{
intr i,j;
intr* p; 
public:
	vect(){p=0;i=0;j=0;};
	vect(intr ii,intr jj):i(ii),j(jj){
	p=new intr[ii];
	for(int j2=0;j2<ii;j2++)
	{*(p+j2)=0;
	if (p==0) throw int(); 
	};};
	~vect(){};
	void re(intr n){j=n;};
	vect& operator=(const vect& vv){i=vv.i;j=vv.j;p=vv.p;return *this;};
	void destroy(){if (p!=0) delete[] p;};
	intr& operator[](intr ii){if (ii>=j) throw int(); return *(p+ii);};
	intr ig(){return j;};
	void show(){
		ofstream f("vector.dat");
		for(int ii=j-1;ii>=0;ii--){
		f.width(8);
		f.fill('0');
		f <<hex<<*(p+ii)<<" ";
		};
	};
};

void mull(intr& rm,intr& rs)
{
   into im,is;
   into om,os;
   intr p1,p2;

   om=rm&0x0000ffff;
   os=rm>>16;
   im=rs&0x0000ffff;
   is=rs>>16;

   p1=im*om;
   rm=p1&0x0000ffff;
   p2=im*os+(p1>>16);
   rm+=p2<<16;
   p1=is*om+(rm>>16);
   rm=(rm&0x0000ffff)+(p1<<16);
   rs=(p2>>16)+is*os+(p1>>16);
};

vect iter(vect v,intr i,vect vn)
{
   intr n;
   if (v[v.ig()-1]>0) n=v.ig()+1; else n=v.ig(); 
   vn.re(n);
   //cout <<n<<"\n";
   intr rm,rs,os=0;
   for(int j=0;j<v.ig();j++)
   {
      rm=i;
      rs=v[j];
      mull(rm,rs);
      _asm{
         mov eax,rm;
         mov ebx,os;
         add eax,ebx;
         adc rs,0;
         mov rm,eax;
      };
      vn[j]=rm;
      os=rs;
   };
   if (os>0) vn[j]=os;
   return vn;
}; 

vect fak(intr i)
{
   vect v1(i,1);v1[0]=1;
   vect v2(i,1);
   vect v,vn;
   v=v1;
   vn=v2;
   for(intr j=2;j<=i;j++)
   {
      vn=iter(v,j,vn);
      //v.destroy();
      v1=v;
      v=vn;
      vn=v1;
   };
   return vn;
};

void main()
{
   vect v;
   v=fak(10000);
   v.show();
   cout <<"\n"<<dec<<v.ig()<<"\n";
}