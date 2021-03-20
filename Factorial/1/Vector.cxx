#ifndef VECTOR_CXX
#define VECTOR_CXX

#ifdef INCLUDE_VERID
   static char verid_Vector_cxx[]="@(#)$RCSfile: $$Revision  $$Date: $ ";
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
* Description:  Vector.cpp: implementation of the vect class.
*
* Caution:      no cautions
*
***********************************************************************/

#include "Vector.hxx"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

template<class T>
inline Vector<T>::Vector() : m_Nstep_memory_resize(STEP_MEMORY_RESIZE)
{
	m_Nsize = 0;
   m_Nsz_mem = 0;
	p_data = NULL;
}

//-----------------------------------------------------------
// Description    : return the pointer on a first element of the data
// Note: call this function only if m_Nsize > 0
//----------------------------------------------------------
template<class T>
inline T* Vector<T>::begin() const
{
	return p_data;
}

//-----------------------------------------------------------
// Description    : return the pointer on a last element of the data
// Note: call this function only if m_Nsize > 0
//----------------------------------------------------------
template<class T>
inline T* Vector<T>::end() const
{
	return p_data+m_Nsize-1;
}

//-----------------------------------------------------------
// Description    : Clear the data in array or number equal to 0
//----------------------------------------------------------
template<class T>
inline void Vector<T>::clear()
{
	m_Nsize = 0;
}

//-----------------------------------------------------------
// Description    : return number of elements
//----------------------------------------------------------
template<class T>
inline int Vector<T>::size() const
{
	return m_Nsize;
}

template<class T>
inline Vector<T>::~Vector()
{
	delete []p_data;
}

//-----------------------------------------------------------
// Description    : Mathematical shift.
//   Example   123<<2 -> 00123
// Parameters:
//    [in] [Parameter 1] Description: number of rights shifts
// Exception: memoryEx
// Note: If i<1 this method do not doing anything with number.
//       The addition memory added authomatically
//----------------------------------------------------------
template<class T>
void Vector<T>::operator<<(int Nnumber)
{
   if(Nnumber>0)
   {
      m_Nsize += Nnumber;
      if(m_Nsize > m_Nsz_mem) 
      {
         // if array p_data needed added memory
         while(m_Nsz_mem < m_Nsize) m_Nsz_mem += m_Nstep_memory_resize;
         T * new_p_data = new T[m_Nsz_mem];

         if(p_data) 
         {
            cpy(new_p_data + Nnumber, p_data, m_Nsize - Nnumber);
            delete []p_data;
         }

         p_data = new_p_data;
      } else
         if(m_Nsize) rcpy(p_data + m_Nsize - 1, p_data + m_Nsize - Nnumber - 1, m_Nsize - Nnumber);
   
      for(int j = 0; j < Nnumber; j++)
         *(p_data + j) = T(0);
   }
}

//-----------------------------------------------------------
// Description    : copy m_sz elements from t2 to t1 in revers order
// Parameters:
//    [inout] [Parameter 1] Description: pointer to target
//    [in]    [Parameter 2] Description: pointer to sourse
//    [in]    [Parameter 3] Description: number of copying elements
// Note: lenth of *p_target and *p_sourse arrays must be more then m_Nsize
//----------------------------------------------------------
template<class T>
void Vector<T>::rcpy(T * p_target, T * p_sourse, int m_Nsize)
{
	while(m_Nsize--) 
		*p_target-- = *p_sourse--;
}

//-----------------------------------------------------------
// Description    : Add element in first place of array, other elements moved
// Parameters:
//    [in]    [Parameter 1] Added element
// Exception: memoryEx
// Note: The addition memory added authomatically
//----------------------------------------------------------
template<class T>
void Vector<T>::push_front(const T& data)
{
	if(m_Nsize == 0)
	{
		push_back(data);
	}
	else
	{
		push_back(*end());
		T * i = end() - 1;
		while(i > begin())
		{
			*i = *( i - 1 );
			--i;
		}
		*p_data = data;
	}
}

//-----------------------------------------------------------
// Description    : assignment statement
// Parameters:
//    [in]    [Parameter 1] Copying object
// Exception: memoryEx
// Note: If needed: the addition memory added authomatically
//----------------------------------------------------------
template<class T>
Vector<T>& Vector<T>::operator=(const Vector<T>& vector)
{
	if( this != &vector )
	{
		m_Nsize = vector.m_Nsize;
		if( m_Nsz_mem < vector.m_Nsize )
		{
			if(p_data) delete p_data;
			p_data = new T[vector.m_Nsz_mem];
			m_Nsz_mem = vector.m_Nsz_mem;
		}
		cpy(p_data, vector.p_data, m_Nsize);
	}
	return *this;
}

//-----------------------------------------------------------
// Description    : swap all descriptions - fast swap
// Parameters:
//    [inout]    [Parameter 1] Swaping object
//----------------------------------------------------------
template<class T>
inline void Vector<T>::swap(Vector<T>& vector)
{
	swap(m_Nsz_mem, vector.m_Nsz_mem);
	swap(m_Nsize,   vector.m_Nsize);
	swap(p_data,    vector.p_data);
}

//-----------------------------------------------------------
// Description    : copy from t2 to t1 m_sz - elements
// Parameters:
//    [inout] [Parameter 1] Description: pointer to target
//    [in]    [Parameter 2] Description: pointer to sourse
//    [in]    [Parameter 3] Description: number of copying elements
// Note: lenth of *p_target and *p_target arrays must be more then m_Nsize
//----------------------------------------------------------
template<class T>
void Vector<T>::cpy(T * p_target, T * p_sourse, int m_Nsize)
{
	while(m_Nsize--) 
		*p_target++ = *p_sourse++;
}

//-----------------------------------------------------------
// Description    : Added element to end of array
// Parameters:
//    [in]    [Parameter 1] Added element
// Exception: memoryEx
// Note: The addition memory added authomatically
//----------------------------------------------------------
template<class T>
void Vector<T>::push_back(const T& t)
{
   ++m_Nsize;
   if(m_Nsize > m_Nsz_mem)
   {
      m_Nsz_mem += m_Nstep_memory_resize;
      T * new_p_data = new T[m_Nsz_mem];
      if(p_data) 
      {
         cpy(new_p_data, p_data, m_Nsize - 1);
         delete []p_data;
      }
      
      p_data = new_p_data;
   }
   *(p_data + m_Nsize - 1) = t;
}

//-----------------------------------------------------------
// Description    : Class vect<T> copy constructor.
//                   Create object as a copy of parameter v
// Parameters:
//    [in]    [Parameter 1] Copiyng object
//----------------------------------------------------------
template<class T>
Vector<T>::Vector(const Vector<T>& vector) : m_Nstep_memory_resize(STEP_MEMORY_RESIZE)
{
   m_Nsize = vector.m_Nsize;
   m_Nsz_mem = 0;
   while(m_Nsz_mem < m_Nsize) 
      m_Nsz_mem += m_Nstep_memory_resize;
   p_data = new T[m_Nsz_mem];
   T * i = vector.p_data;
   T * j = p_data;
   while(i<=vector.end())
      *j++ = *i++;
}

//-----------------------------------------------------------
// Description    : Class vect<T> constructor.
//                   Create object with reserved memory
// Parameters:
//    [in]    [Parameter 1] the size of reserved memory
//----------------------------------------------------------
template<class T>
Vector<T>::Vector(int Nnumber) : m_Nstep_memory_resize(STEP_MEMORY_RESIZE)
{
	m_Nsize = 0;
	if (Nnumber > 0) 
	{
		m_Nsz_mem = Nnumber;
		p_data = new T[Nnumber];
	}
	else
	{
		m_Nsz_mem = 0;
		p_data = NULL;
	}
}

#endif