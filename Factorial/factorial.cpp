#include<vector>
#include<iostream>
#include<fstream>
#include <time.h>
#include <sys/timeb.h> 

using namespace std;

#define foundation 10000

typedef unsigned short elem;
typedef unsigned long calc;
typedef vector<elem> vect; 

class SuperLong{
vect mass;
vect::iterator it;
elem ost,rez0,rez1,rez2,rem0,rem1,rem2,mul_m,mul_s;
calc temp_c;
public:
   SuperLong();
   SuperLong::SuperLong(SuperLong& SL):mass(SL.mass){};
  ~SuperLong();
   SuperLong& operator*(elem);
   SuperLong& operator*(const calc );
   SuperLong& operator+=(const SuperLong&);
   SuperLong& operator=(const SuperLong&);
   SuperLong& operator<<(ostream&);
   SuperLong& operator>(elem);
   SuperLong& factorial(calc );
};

SuperLong::SuperLong():mass(1)
{
   mass[0]=1;
}

SuperLong& SuperLong::operator=(const SuperLong& SL)
{
   mass=SL.mass;
   return *this;
}
   
SuperLong::~SuperLong(){}

SuperLong& SuperLong::operator*(elem mul)
{
   if (mul>(foundation-1)) throw mul;
   ost=0;
   it=mass.begin();
   while(it!=mass.end())
   {
      temp_c=(*it)*mul+ost;
      *it=temp_c%foundation;
      ost=temp_c/foundation;
      ++it;
   }
   if (ost>0) mass.push_back(ost);
return *this;
}

SuperLong& SuperLong::operator*(const calc mul)
{
	if (mul>(foundation*foundation-1)) throw mul;
	
	mul_m=mul%foundation;
    mul_s=mul/foundation;
    rem0=rem1=rem2=0; 
	
	it=mass.begin();
	while(it!=mass.end())
    {
     
	 temp_c=mul_m*(*it);
     rez0=temp_c%foundation;
     temp_c=mul_s*(*it)+(temp_c/foundation);
     rez1=temp_c%foundation;
     rez2=temp_c/foundation;
   
     ost=rem0+rez0;
     *it=ost%foundation;
     ost/=foundation;
   
     ost=rem1+rez1+ost;
     rem0=ost%foundation;
     ost/=foundation;
   
     ost=rem2+rez2+ost;
     rem1=ost%foundation;
     rem2=ost/foundation;
	 ++it;
	}
	if (rem2>0){mass.push_back(rem0);mass.push_back(rem1);mass.push_back(rem2);}
	else if(rem1>0){mass.push_back(rem0);mass.push_back(rem1);}
	else if(rem0>0){mass.push_back(rem0);}
return *this;         
};

SuperLong& SuperLong::operator<<(ostream& o)
{
   vect::reverse_iterator rit=mass.rbegin();
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

SuperLong& SuperLong::operator>(elem shift)
{
   vect temp;
   while(shift){temp.push_back(0);--shift;}
   it=mass.begin();
   while(it!=mass.end()){temp.push_back(*it);++it;}
   this->mass.swap(temp);
return *this;
}


SuperLong& SuperLong::operator+=(const SuperLong& SL)
{
   ost=0;
   elem sum1,sum2;
   calc tmp; 
   vect temp;
   it=mass.begin();
   vect::const_iterator cit=SL.mass.begin();

   while(cit!=SL.mass.end()||it!=mass.end())
   {
      if(it >= mass.end()) sum1 = 0; 
		else 
		{
			sum1 = *it;
			++it;
		}
		if(cit >= SL.mass.end()) sum2 = 0; 
		else 
		{
			sum2 = *cit;
			++cit;
		}
		tmp = sum1 + sum2 + ost;
		temp.push_back(tmp % foundation);
		if(tmp >= foundation) ost = 1; else ost = 0;
   }
   if(ost) temp.push_back(ost);
   this->mass.swap(temp);
return *this;
}

SuperLong& SuperLong::factorial(calc fac)
{
   mass.clear();
   mass.push_back(1);
   if (fac>1)
   {
	   if (fac<foundation)
	   {
		   elem fac_e=fac;
		   while(fac_e>1){(*this)*fac_e;--fac_e;}
	   } else
	   {
		   elem fac_e=foundation-1;
		   while(fac_e>1){(*this)*fac_e;--fac_e;}
		   calc fac_c=foundation;
		   while(fac_c<=fac){(*this)*fac_c;++fac_c;}
	   }
   }
return *this;
}



void main()
{
   SuperLong s;
   calc rep;
   cout <<"This program calculate factorial of any number, press 0 to leave\n";
   while(rep>0)
   {
   cout <<"enter x: ";
   cin>>rep;
   time_t ltime;
   _timeb tstruct;
   time( &ltime );
   _ftime( &tstruct );
   long t = ltime*1000+tstruct.millitm;

   s.factorial(rep);

   time( &ltime ); 
   _ftime( &tstruct ); 
   
   ofstream f("pr.txt");
   cout<<rep<<"!=";
   s<<cout<<f;

   cout<<endl<<"Calculated "<<ltime*1000+tstruct.millitm-t<<" milliseconds"<<endl;
   }

}

 