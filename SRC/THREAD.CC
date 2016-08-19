/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: thread.cc 1.2 1995/08/13 03:21:12 teb Exp $ */


#include<thread.h>


//-----------------------------------------------------
//
TThread::TThread(PFNTHREAD func, ULONG args, ULONG stackSize)
{
   threadFunc = func;
   fThreadArg = args;
   fStackSize = stackSize;  
}


//-----------------------------------------------------
//
TThread::~TThread()
{
   exitThread();
}



//-----------------------------------------------------
//
BOOL TThread::init(BOOL active)
{
   APIRET rc;
   ULONG flag;

   if (active)
      flag = 0L;
   else
      flag = 1L;

   rc = DosCreateThread(&threadId, threadFunc, 
           fThreadArg, flag, fStackSize);

   return (BOOL)!rc;
}



//-----------------------------------------------------
//
BOOL TThread::setPriority(ULONG delta)
{
  APIRET rc;

  rc =   DosSetPriority(PRTYS_THREAD, PRTYC_NOCHANGE, delta, threadId);

   return (BOOL)rc;
}
 


//-----------------------------------------------------
//
void TThread::suspend()
{
   DosSuspendThread(threadId);
}



//-----------------------------------------------------
//
void TThread::resume()
{
   DosResumeThread(threadId);
}




//-----------------------------------------------------
//
TID TThread::inqThreadId()
{
   return threadId;
}
 



//-----------------------------------------------------
//
void TThread::enterCritical()
{
   DosEnterCritSec();
}



//-----------------------------------------------------
//
void TThread::exitCritical()
{
   DosExitCritSec();
}


//-----------------------------------------------------
//
void TThread::waitThread()
{
   DosWaitThread(&threadId, 0);
}


//-----------------------------------------------------
//
void TThread::exitThread()
{
   DosExit(EXIT_THREAD, 0);
}





