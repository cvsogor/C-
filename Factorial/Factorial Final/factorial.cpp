#include<vector>
#include<iostream>
#include<fstream>

using namespace std;

typedef unsigned short elem;
typedef unsigned long calc;
typedef vector<elem> vect; 

class SuperLong{
vect mass;
vect::iterator it;
vect::reverse_iterator rit;
calc prom,count;
elem ost;
public:
   SuperLong();
   SuperLong::SuperLong(SuperLong& SL):mass(SL.mass){};
  ~SuperLong();
   SuperLong& operator*(elem);
   SuperLong& operator+=(const SuperLong&);
   SuperLong& operator=(const SuperLong&);
   SuperLong& operator<<(ostream&);
   SuperLong& operator>(elem);
   SuperLong& factorial(calc e);

};
SuperLong& SuperLong::operator*(elem e)
{
   ost=0;
   it=mass.begin();
   while(it!=mass.end())
   {
      prom=(*it)*e+ost;
      *it=prom%10000;
      ost=prom/10000;
      ++it;
   }
   if (ost>0) {mass.push_back(ost);ost=0;}
   return *this;
}
SuperLong& SuperLong::operator<<(ostream& o)
{
   rit=mass.rbegin();
   while(rit!=mass.rend())
   {
      o.width(4);
      o.fill('0');
      o<<(*rit)<<' ';
      ++rit;
   }
   o<<'\n';
   return *this;
}
SuperLong& SuperLong::operator>(elem e)
{
   vect temp;
   while(e){temp.push_back(0);--e;}
   it=mass.begin();
   while(it!=mass.end()){temp.push_back(*it);++it;}
   this->mass.swap(temp);
   return *this;
}

SuperLong::SuperLong():mass(1)
{
   mass[0]=1;
}
SuperLong& SuperLong::operator=(const SuperLong& SL)
{
   mass=SL.mass;
   return *this;
}
   
SuperLong::~SuperLong()
{

}
SuperLong& SuperLong::operator+=(const SuperLong& SL)
{
   ost=0;
   elem r1,r2;
   calc tmp; 
   vect temp;
   it=mass.begin();
   vect::const_iterator cit=SL.mass.begin();

   while(cit!=SL.mass.end()||it!=mass.end())
   {
      if(it >= mass.end()) r1 = 0; 
		else 
		{
			r1 = *it;
			++it;
		}
		if(cit >= SL.mass.end()) r2 = 0; 
		else 
		{
			r2 = *cit;
			++cit;
		}
		tmp = r1 + r2 + ost;
		temp.push_back(tmp % 10000);
		if(tmp >= 10000) ost = 1; else ost = 0;
   }
   if(ost) temp.push_back(ost);
	this->mass.swap(temp);

   return *this;
}
SuperLong& SuperLong::factorial(calc e)
{
   count=0;
   calc bank=1;
   elem cur;
   mass.clear();
   mass.push_back(1);
   if ((e==0)||(e==1)) return *this;
   for(calc i=2;i<=e;++i)
   {
      if ((i<10000/*60000*/)&&(bank<100000)) {bank*=i;}
      else
      {
         //while(bank>1)
         //{
            SuperLong help_main(*this);
            cur=bank%10000;
            bank/=10000;
            (*this)*cur;
            if (bank>0)
            {
               cur=bank%10000;
               bank/=10000;
               SuperLong help(help_main);
               help*cur;
               help>1;
               (*this)+=help;
            }
            if (bank>0)
            {
               cur=bank%10000;
               bank/=10000;
               SuperLong help(help_main);
               help*cur;
               help>2;
               (*this)+=help;
            }


         //}
      bank=i;
         //cout<<i-1<<' ';
         //(*this)<<cout;
               
      }
   }
   if (bank>1)
      while(bank)
         {
            cur=bank%10000;
            bank/=10000;
            (*this)*cur;
            if (bank>0)
            {
               cur=bank%10000;
               bank/=10000;
               SuperLong help(*this);
               help*cur;
               help>1;
               (*this)+=help;
            }
            if (bank>0)
            {
               cur=bank%10000;
               bank/=10000;
               SuperLong help(*this);
               help*cur;
               help>2;
               (*this)+=help;
            }
         }

   return *this;
} 
void main()
{
//cout<<sizeof(unsigned short);
SuperLong s;
s.factorial(9999);
ofstream f("pr.txt");
s<<cout<<f;
/*s1*65535*65535*65535;
s2*65535*65535*65535;
s1+=s2;
s1<<cout;
s1>2;
s1<<cout;*/
} 