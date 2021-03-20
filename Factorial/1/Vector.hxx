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
* Description:  Vector.h: interface for the Vector class.
*
* Caution:      no cautions
*
***********************************************************************/
#if !defined(AFX_VECT_H__8587053F_9214_4F8D_A2EA_63DEB1090408__INCLUDED_)
#define AFX_VECT_H__8587053F_9214_4F8D_A2EA_63DEB1090408__INCLUDED_

#ifdef INCLUDE_VERID
   static char verid_Vector_hxx[]="@@(#)$RCSfile: $$Revision  $$Date: $ ";
#endif

#include<math.h>
#include<iostream.h>
#include<string.h>
#include<new.h>

#define STEP_MEMORY_RESIZE  10000
/* class vect<class T> contain a array whis desired lenth */
template<class T>
class Vector  
{
public:
//-----------------------------------------------------------
// Description    : Class vect<T> constructor.
//                   Create object with reserved memory
// Parameters:
//    [in]    [Parameter 1] the size of reserved memory
//----------------------------------------------------------
   explicit Vector(int Nsize);
//-----------------------------------------------------------
// Description    : Class vect<T> copy constructor.
//                   Create object as a copy of parameter "vector"
// Parameters:
//    [in]    [Parameter 1] Copiyng object
//----------------------------------------------------------
	Vector(const Vector<T>& vector);
//-----------------------------------------------------------
// Description    : return the pointer on a first(last) element of the data
// Notes: Do not verify a pointer p_data
//----------------------------------------------------------
	T* begin() const;
	T* end() const;
//-----------------------------------------------------------
// Description    : Clear the data in array or number equal to 0
// Note: Do not release a memory
//----------------------------------------------------------
	void clear();
//-----------------------------------------------------------
// Description    : Added element to end(begin) of array
// Parameters:
//    [in]    [Parameter 1] Added element
// Exception: memoryEx
// Note: The addition memory added authomatically
//----------------------------------------------------------
	void push_back(const T& data);
	void push_front(const T& data);
//-----------------------------------------------------------
// Description    : swap all descriptions of objects - fast swap of containers
// Parameters:
//    [inout]    [Parameter 1] Swaping object
//----------------------------------------------------------
	void swap(Vector<T>& v);
//-----------------------------------------------------------
// Description    : return number of elements
//----------------------------------------------------------
	int size() const;
//-----------------------------------------------------------
// Description    : assignment statement
// Parameters:
//    [in]    [Parameter 1] Copying object
// Exception: memoryEx
// Note: The addition memory added authomatically
//----------------------------------------------------------	
   Vector<T>& operator=(const Vector<T>& vector);
	Vector();
   ~Vector();
//-----------------------------------------------------------
// Description    : Mathematical shift.
//   Example   123<<2 -> 00123
// Parameters:
//    [in] [Parameter 1] Description: number of rights shifts
// Exception: memoryEx
// Note: If i<1 this method do not doing anything with number.
//       The addition memory added authomatically
//----------------------------------------------------------
	void operator<<(int i);
private:
// size of memory, that use this object
	int m_Nsz_mem;
// number of elements
	int m_Nsize;
// if desired lenth more then m_sz_mem, m_sz_mem += m_step_memory_resize
	const int m_Nstep_memory_resize;
// a poiter to contained data array
	T * p_data;
//-----------------------------------------------------------
// Description    : copy from p_sourse to p_target m_sz - elements (in revers order)
// Parameters:
//    [inout] [Parameter 1] Description: pointer to target
//    [in]    [Parameter 2] Description: pointer to sourse
//    [in]    [Parameter 3] Description: number of copying elements
// Note: lenth of *p_target and *p_sourse arrays must be more then m_sz
//----------------------------------------------------------
	void  cpy(T * p_target, T * p_sourse, int Nnumber);
	void rcpy(T * p_target, T * p_sourse, int Nnumber);
//-----------------------------------------------------------
// Description    : swap two object (variables)
// Parameters:
//    [inout]    [Parameter 1] Swaping object
//----------------------------------------------------------
template<class TT>
	void swap(TT& data1, TT& data2)
	{
		TT tmp_data = data1;
		data1 = data2;
		data2 = tmp_data;
	};
};

#endif // !defined(AFX_VECT_H__8587053F_9214_4F8D_A2EA_63DEB1090408__INCLUDED_)

