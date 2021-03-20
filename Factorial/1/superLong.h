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
* Description:  SuperLong.h: interface for the SuperLong class.
*
* Caution:      no cautions
*
***********************************************************************/
#if !defined(AFX_SUPERLONG_H__1A60A5CB_CA5A_4DB0_85BF_38E7FCFCA43D__INCLUDED_)
#define AFX_SUPERLONG_H__1A60A5CB_CA5A_4DB0_85BF_38E7FCFCA43D__INCLUDED_

#ifdef INCLUDE_VERID
   static char verid_superLong_h[]="@(#)$RCSfile: $$Revision  $$Date: $ ";
#endif

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "Vector.cxx"

#define START_NUMBER_LENGTH 10000
// type the type of data wich used for calculations
//typedef unsigned char calculate_type;
//#define MAX_VALUE_OF_NUMERAL 100
typedef unsigned short calculate_type;
#define MAX_VALUE_OF_NUMERAL 10000

#define NUMBER_LENGTH 200
/* Class SuperLong.
   All digits the number are writing to container in revers order
   Example: 123456 write as 65432.
*/
class SuperLong  
{
public:
//-----------------------------------------------------------
// Description    : assignment statement
//[ Parameters:]
//    [in] [Parameter 1] copying object
// [Exception: MemoryEx]
//----------------------------------------------------------
   SuperLong& operator =(const SuperLong &SL);
//-----------------------------------------------------------
// Description    : Convert long (string) to SuperLong
//[ Parameters:]
//    [in] [Parameter 1] long number
// [Exception: MemoryEx]
//----------------------------------------------------------
   SuperLong& operator =(unsigned long Nnumber);
   SuperLong& operator =(const char * Sznumber);
	SuperLong(unsigned long Nnumber);
   SuperLong(const char* Bnumber);
//-----------------------------------------------------------
// Description    : Matematicals operations ==, <= > and other
//[ Parameters:]
//    [in] [Parameter 1] long number
// [Return: result of collation]
//----------------------------------------------------------
	bool operator ==(const SuperLong &SL_number);
	bool operator ==(unsigned long Nnumber);
	bool operator <=(SuperLong &SL);
	bool operator <(SuperLong &SL);
	bool operator >=(SuperLong &SL);
	bool operator >(SuperLong &SL);
   void operator +=(SuperLong &SL);
	void operator *=(SuperLong &SL);
//-----------------------------------------------------------
// Description    : prefix and postfix increments
// [Exception: MemoryEx]
//----------------------------------------------------------
   SuperLong& operator++();
	SuperLong  operator++(int i);
//-----------------------------------------------------------
// Description    : Simple constructor
// Note: Rezerved 100 bytes for number
//----------------------------------------------------------
	SuperLong();
	SuperLong& factorial();
//-----------------------------------------------------------
// Description    : Copy constructor
//[ Parameters:]
//    [in] [Parameter 1] copying object
// [Exception: MemoryEx]
//-----------------------------------------------------------
	SuperLong(const SuperLong& SL);
	virtual ~SuperLong();
//-----------------------------------------------------------
// Description    : sream [in/out]put of SuperLong number
//----------------------------------------------------------
	friend ostream& operator<<(ostream& o, const SuperLong& l);
	friend istream& operator>>(istream& i, SuperLong& sl);
private:
//-----------------------------------------------------------
// Description    : SuperLong multiply by one digit
//[ Parameters:]
//    [in] [Parameter 1] digit
// [Exception: MemoryEx]
// Note: 0<= Bdigit <=9
//----------------------------------------------------------
   void operator *=(calculate_type ch);
	SuperLong operator *(calculate_type ch);
//-----------------------------------------------------------
// Description    : Add digit to SuperLong
//[ Parameters:]
//    [in] [Parameter 1] digit
// [Exception: MemoryEx]
// Note: 0<= Bdigit <=9
//----------------------------------------------------------
   void operator +=(calculate_type ch);
	SuperLong operator +(calculate_type ch);
/* addition structure: contain ten results of multiplication
   x*y*exp(10000,power)
   */
	struct Rez
	{
      // pointer to SuperLong
		SuperLong* p_slg;
      // power of SuperLong
		unsigned int m_Npower;
//-----------------------------------------------------------
// Description    : Constructor of additional structure
//----------------------------------------------------------
		Rez(); 
//-----------------------------------------------------------
// Description    : Constructor of additional structure
//----------------------------------------------------------
		~Rez();
	} rez;
// used container for digits
	typedef Vector<calculate_type> container;
// number in memory
	container m_number;
// temp number, used in addition algorithm
	container m_temp_for_sub;
// temp number, used in multiplication algorithm
   SuperLong * m_temp_for_mul;
//-----------------------------------------------------------
// Description    : clear: assign 0 to number
// Note: Do not release a memory
//----------------------------------------------------------
   void clear();
};

#endif // !defined(AFX_SUPERLONG_H__1A60A5CB_CA5A_4DB0_85BF_38E7FCFCA43D__INCLUDED_)