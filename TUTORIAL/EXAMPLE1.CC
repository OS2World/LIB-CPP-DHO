/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: example1.cc 1.1 1995/08/30 01:16:39 teb Exp $ */

/*******************************************
 *   Example1.cc or, "Your very own        *
 *   Presentation Manager App with         *
 *   a mere 2 function calls!"             *
 *                                         *
 *   This is the basis of a DHO based      *
 *   OS/2 application.  The main event     *
 *   loop constructs an application object *
 *   and instructs it to begin it's event  *
 *   loop.                                 *
 *******************************************/

//DHO application object header file
#include<applicat.h>


#define kAppId 100


//=========================================
//  program entry point
INT main(void)
{
   TApplication app(kAppId);

   app.init();     // initialize object
   app.run();      // begin event loop          

   return 0;
}