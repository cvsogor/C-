#ifndef NO_VERID
   static char verid_SuperLong[]="@(#)$RCSfile: $$Revision  $$Date: $ ";
#endif
/***********************************************************************
*  This module is part of the BC
* Copyright (c) Soft Computer Consultants, Inc.  2005
*    All Rights Reserved
* This document contains unpublished, confidential and proprietary
* information of Soft Computer Consultants, Inc. No disclosure or use of
* any portion of the contents of these materials may be made without the
* express written consent of Soft Computer Consultants, Inc.
*
* Author:   Vladimir Gorbenko
* Description:  SuperLong.cpp: implementation of the SuperLong class.
*
* Caution:      no cautions
*
***********************************************************************/

#include "superLong.h"
#include <stdlib.h>

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

//-----------------------------------------------------------
// Description    : Constructor of additional structure
//----------------------------------------------------------
inline SuperLong::Rez::Rez()
{ 
   p_slg = NULL;
   m_Npower = 0; 
}

//-----------------------------------------------------------
// Description    : Constructor of additional structure
//----------------------------------------------------------
inline SuperLong::Rez::~Rez()
{
   delete p_slg;
}

//-----------------------------------------------------------
// Description    : assignment statement
//[ Parameters:]
//    [in] [Parameter 1] copying object
// [Exception: MemoryEx]
//----------------------------------------------------------
inline SuperLong& SuperLong::operator =(const SuperLong &SL)
{
   if(this != &SL)
	   m_number = SL.m_number;
	return *this;
}

//-----------------------------------------------------------
// Description    : Matematicals operations ==
//[ Parameters:]
//    [in] [Parameter 1] long number
// [Return: result of collation]
//----------------------------------------------------------
inline bool SuperLong::operator ==(unsigned long Nnumber)
{
	return (*this) == SuperLong(Nnumber);
}

//-----------------------------------------------------------
// Description    : Matematicals operations >=
//[ Parameters:]
//    [in] [Parameter 1] SuperLong number
// [Return: result of collation]
//----------------------------------------------------------
inline bool SuperLong::operator >=(SuperLong &SL)
{
	return !(*this < SL);
}

//-----------------------------------------------------------
// Description    : Matematicals operations >
//[ Parameters:]
//    [in] [Parameter 1] SuperLong number
// [Return: result of collation]
//----------------------------------------------------------
inline bool SuperLong::operator >(SuperLong &SL)
{
	return !(*this <= SL);
}

//-----------------------------------------------------------
// Description    : Convert string to SuperLong number
//[ Parameters:]
//    [in] [Parameter 1] string that contained a number
// [Exception: MemoryEx]
// Note: String must be contain only digits, else all accounts shall be incorect
//-----------------------------------------------------------
SuperLong::SuperLong(const char * Sznumber) : m_number(START_NUMBER_LENGTH)
{
	long i = atoi(Sznumber);
   m_temp_for_mul = NULL;
	*this = i;
}

//-----------------------------------------------------------
// Description    : Convert long to SuperLong number
//[ Parameters:]
//    [in] [Parameter 1] number to converting
//-----------------------------------------------------------
inline SuperLong::SuperLong(unsigned long Nnumber) : m_number(START_NUMBER_LENGTH)
{
	m_temp_for_mul = NULL;
	*this = Nnumber;
}

//-----------------------------------------------------------
// Description    : Copy constructor
//[ Parameters:]
//    [in] [Parameter 1] copying object
// [Exception: MemoryEx]
//-----------------------------------------------------------
inline SuperLong::SuperLong(const SuperLong& SL)
{
	m_temp_for_mul = NULL;
	m_number=SL.m_number;
}

//-----------------------------------------------------------
// Description    : Simple constructor
// Note: Rezerved 100 bytes for number
//----------------------------------------------------------
inline SuperLong::SuperLong() : m_number(START_NUMBER_LENGTH)
{
	m_temp_for_mul = NULL;
}

//-----------------------------------------------------------
// Description    : Destructor
//----------------------------------------------------------
inline SuperLong::~SuperLong()
{
   delete m_temp_for_mul;
}

//-----------------------------------------------------------
// Description    : Convert long to SuperLong
//[ Parameters:]
//    [in] [Parameter 1] long number
// [Exception: MemoryEx]
//----------------------------------------------------------
SuperLong& SuperLong::operator =(unsigned long Nnumber)
{
	clear();
	unsigned long temp;
	unsigned long i=0;
	if(Nnumber == 0) 
	{
		m_number.push_back(char(Nnumber));
		return *this;
	}
	while(Nnumber)
	{
      temp = (unsigned long) (Nnumber- (unsigned long) (Nnumber/MAX_VALUE_OF_NUMERAL)*MAX_VALUE_OF_NUMERAL);
      m_number.push_back((calculate_type) temp);
      Nnumber=long(Nnumber/MAX_VALUE_OF_NUMERAL);
	}
	return *this;
}

//-----------------------------------------------------------
// Description    : Convert string to SuperLong
//[ Parameters:]
//    [in] [Parameter 1] string whis number
// [Exception: MemoryEx]
//----------------------------------------------------------
SuperLong& SuperLong::operator =(const char * Sznumber)
{
	clear();
	while(*Sznumber)
	{
		m_number.push_front(*Sznumber++-48);
	}
	return *this;
}

//-----------------------------------------------------------
// Description    : clear: assign 0 to number
// Note: Do not release a memory
//----------------------------------------------------------
inline void SuperLong::clear()
{
	m_number.clear();
}

//-----------------------------------------------------------
// Description    : SuperLong multiply by one digit
//[ Parameters:]
//    [in] [Parameter 1] digit
// [Exception: MemoryEx]
// Note: 0<= Bdigit <=9
//----------------------------------------------------------
void SuperLong::operator *=(calculate_type Bdigit)
{
	calculate_type * it = m_number.begin();
	unsigned int ost = 0;
	while(it<=m_number.end())
	{
		unsigned int temp = *it*Bdigit;
		temp+=ost;
		*it = temp%MAX_VALUE_OF_NUMERAL;
		ost = (unsigned long) (temp/MAX_VALUE_OF_NUMERAL);
		++it;
	}
	if(ost) m_number.push_back(ost);
}

//-----------------------------------------------------------
// Description    : SuperLong multiply by one digit
//[ Parameters:]
//    [in] [Parameter 1] digit
// [Exception: MemoryEx]
// Note: 0<= Bdigit <=9
//----------------------------------------------------------
inline SuperLong SuperLong::operator *(calculate_type Bdigit)
{
	SuperLong t_sLg = *this;
	t_sLg *= Bdigit;
	return t_sLg;
}

//-----------------------------------------------------------
// Description    : Add digit to SuperLong
//[ Parameters:]
//    [in] [Parameter 1] digit
// [Exception: MemoryEx]
// Note: 0<= Bdigit <=9
//----------------------------------------------------------
void SuperLong::operator +=(calculate_type Bdigit)
{
	calculate_type * it = m_number.begin();

	unsigned long ost = 0;
	unsigned long temp = *it+Bdigit;
	*it = (calculate_type) temp%MAX_VALUE_OF_NUMERAL;
	if(temp>=MAX_VALUE_OF_NUMERAL) ost = 1;
	++it;
	while(it <= m_number.end())
	{
		temp = *it+ost;
		*it = (calculate_type) temp%MAX_VALUE_OF_NUMERAL;
		if(temp<MAX_VALUE_OF_NUMERAL) return;
		++it;
	}
	if(ost) m_number.push_back((calculate_type) ost);
}

//-----------------------------------------------------------
// Description    : Add digit to SuperLong
//[ Parameters:]
//    [in] [Parameter 1] digit
// [Exception: MemoryEx]
// Note: 0<= Bdigit <=9
//----------------------------------------------------------
inline SuperLong SuperLong::operator +(calculate_type Bdigit)
{
	SuperLong t_sLg = *this;
	t_sLg += Bdigit;
	return t_sLg;
}

//-----------------------------------------------------------
// Description    : Add argument(SuperLong) to SuperLong
//[ Parameters:]
//    [in] [Parameter 1] SuperLong number
// [Exception: MemoryEx]
//----------------------------------------------------------
void SuperLong::operator +=(SuperLong &SL)
{
	m_temp_for_sub.clear();

	calculate_type * it1 =    m_number.begin();
	calculate_type * it2 = SL.m_number.begin();
	unsigned int tmp, ost = 0;
	unsigned int r1, r2;
	while(it1 <= m_number.end() || it2 <= SL.m_number.end())
	{
		if(it1 > m_number.end()) r1 = 0; 
		else 
		{
			r1 = *it1;
			++it1;
		}
		if(it2 > SL.m_number.end()) r2 = 0; 
		else 
		{
			r2 = *it2;
			++it2;
		}
		tmp = r1 + r2 + ost;
		m_temp_for_sub.push_back(tmp % MAX_VALUE_OF_NUMERAL);
		if(tmp >= MAX_VALUE_OF_NUMERAL) ost = 1; else ost = 0;
	}
	if(ost) m_temp_for_sub.push_back(ost);
	this->m_number.swap(m_temp_for_sub);
}

//-----------------------------------------------------------
// Description    : Multiply SuperLong by argument(SuperLong)
//[ Parameters:]
//    [in] [Parameter 1] SuperLong number
// [Exception: MemoryEx]
//----------------------------------------------------------
void SuperLong::operator *=(SuperLong &SL)
{
	if(!rez.p_slg) rez.p_slg = new SuperLong();
   rez.p_slg->clear();
   rez.m_Npower = 0;

   unsigned int Npower = 0;
	
	if(m_temp_for_mul == NULL) m_temp_for_mul = new SuperLong();
	m_temp_for_mul->clear();

	calculate_type * it = SL.m_number.begin();
	while(it <= SL.m_number.end())
	{
      if(*it)
      {
         *rez.p_slg = *this;
         if(*it != 1) *rez.p_slg *= (*it);
      } else
         rez.p_slg->clear();

		if(*it) rez.p_slg->m_number<<(Npower - rez.m_Npower);
		
      rez.m_Npower = Npower;
		
		*m_temp_for_mul += *(rez.p_slg);
		++it;
		++Npower;
	}
	this->m_number.swap(m_temp_for_mul->m_number); 
}

//-----------------------------------------------------------
// Description    : prefix increment 
// [Exception: MemoryEx]
//----------------------------------------------------------
inline SuperLong& SuperLong::operator++()
{
	*this+=1;
	return *this;
}

//-----------------------------------------------------------
// Description    : postfix increment
// [Exception: MemoryEx]
//----------------------------------------------------------
inline SuperLong SuperLong::operator++(int i)
{
	SuperLong temp = *this;
	++*this;
	return temp;
}

//-----------------------------------------------------------
// Description    : Matematicals operations ==
//[ Parameters:]
//    [in] [Parameter 1] SuperLong number
// [Return: result of collation]
//----------------------------------------------------------
bool SuperLong::operator ==(const SuperLong &SL)
{
	if(SL.m_number.size()==m_number.size())
	{
		const calculate_type * it1 =    m_number.begin();
		const calculate_type * it2 = SL.m_number.begin();
		while(it1<=m_number.end())
		{
			if(*it1!=*it2) return false;
			++it1;++it2;
		}
		return true;
	}
	return false;
}

//-----------------------------------------------------------
// Description    : Matematicals operations <=
//[ Parameters:]
//    [in] [Parameter 1] SuperLong number
// [Return: result of collation]
//----------------------------------------------------------
bool SuperLong::operator <=(SuperLong &SL)
{
	if(m_number.size()<SL.m_number.size()) return true;
	else
	if(m_number.size()>SL.m_number.size()) return false;
	else
	{
		calculate_type * it1 =    m_number.end();
		calculate_type * it2 = SL.m_number.end();
		while(it1>=m_number.begin())
		{
			if(*it1<*it2) return true;
			if(*it1>*it2) return false;
			--it1;--it2;
		}
		return true;
	}
}

//-----------------------------------------------------------
// Description    : Matematicals operations <=
//[ Parameters:]
//    [in] [Parameter 1] SuperLong number
// [Return: result of collation]
//----------------------------------------------------------
bool SuperLong::operator <(SuperLong &SL)
{
	if(m_number.size()<SL.m_number.size()) return true;
	else
	if(m_number.size()>SL.m_number.size()) return false;
	else
	{
		calculate_type * it1 =    m_number.end();
		calculate_type * it2 = SL.m_number.end();
		while(it1>=m_number.begin())
		{
			if(*it1<*it2) return true;
			if(*it1>*it2) return false;
			--it1;--it2;
		}
		return false;
	}
}

//-----------------------------------------------------------
// Description    : Calculate factorial
// [Return: result of calculation (factorial of number(SuperLong)]
// [Exception: MemoryEx]
// [Note: You must undestend, that already 100000! have 456 574 digits and calculated several hours]
//----------------------------------------------------------
SuperLong& SuperLong::factorial()
{
	if((*this) == 0) 
	{
		*this = 1;
		return *this;
	}
	SuperLong temp1 = 2, temp2 = *this;
	while(temp1 < temp2)
	{
		*this *= temp1;
//      cout<<endl<<temp1;
		++temp1;
	}
   return *this;
}

//-----------------------------------------------------------
// Description    : sream output of SuperLong number
//----------------------------------------------------------
ostream& operator<<(ostream& o, const SuperLong& SL)
{
   const calculate_type * it = SL.m_number.end();
   o<<*it;
   --it;
	for( ; it >= SL.m_number.begin(); --it)
	{
      char p = 3 - char(log10((float)*it));
      for( int i = 0; i < p; ++i) o<<"0";
      if( *it )
      {
         o<<int(*it);
      } else
         o<<"0";
	}
   return o;
};

//-----------------------------------------------------------
// Description    : read SuperLong number from input stream
//----------------------------------------------------------
istream& operator>>(istream& i, SuperLong& SL)	
{
	static char buffer[NUMBER_LENGTH];
	i.getline(buffer, NUMBER_LENGTH);
	SL = buffer;
	return i;
};
