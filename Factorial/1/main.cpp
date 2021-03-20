#ifndef NO_VERID
   static char verid_main[]="@(#)$RCSfile: $$Revision  $$Date: $ ";
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
* Description:  Contains main function of the program
*
* Caution:      no cautions
*
***********************************************************************/
#include<fstream.h>
#include <time.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/timeb.h>
#include "superLong.h"

#ifdef WIN32

   #define START \
       time_t ltime;\
      _timeb tstruct;\
      time( &ltime );\
      _ftime( &tstruct );\
      long t = ltime*1000+tstruct.millitm;
   #define END \
      time( &ltime ); \
      _ftime( &tstruct ); 
   #define PRINT \
      cout<<endl<<"Calculated "<<ltime*1000+tstruct.millitm-t<<" milliseconds"<<endl;

#else

   #define END ;
   #define PRINT ;
   #define START ;

#endif

int main()
{
	// x - number for calculation
	char x[NUMBER_LENGTH] = "";
   cout<<" This program calculate the factorial of the number x";
   while(1)
   {
      cout<<"\nInput x, please (press \'q\' to exit)";
      cin.getline(x,NUMBER_LENGTH);
      if ( strcmp(x, "q") == 0 )
         return 0;
      SuperLong s_lg(x);
      cout<<s_lg<<"!=";
	   // start calculate
      START
//   fstream f("1 000 000.txt",3);
      s_lg.factorial();
      END
      cout<<s_lg<<endl;
      PRINT
   }

   return 0;
}
