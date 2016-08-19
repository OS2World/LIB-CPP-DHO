/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: thread.h 1.2 1995/08/13 03:21:12 teb Exp $ */


#ifndef __THREAD_H__
#define __THREAD_H__

#define INCL_DOSPROCESS
#include<os2.h>

#include<object.h>

#define DEFAULT_STACK_SIZE 4096



class TThread : public TObject
{
      TID threadId;
      ULONG fStackSize, fThreadArg;
      PFNTHREAD threadFunc;

   public:
      TThread(PFNTHREAD func, ULONG args, ULONG stackSize);
      virtual ~TThread();
      virtual BOOL init(BOOL active);
      BOOL setPriority(ULONG delta);
      void suspend();
      void resume();
      void enterCritical();
      void exitCritical();
      void exitThread();
      void waitThread();

      TID inqThreadId();
};


#endif
