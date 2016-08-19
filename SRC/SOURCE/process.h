/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: process.h 1.4 1995/08/13 03:21:12 teb Exp $ */


#ifndef __PROCESS_H__
#define __PROCESS_H__
#define INCL_WIN
#include <os2.h>
#include<object.h>


class TProcess : public TObject
{

      HAB hAnchrBlk;
      HMQ hMsgQue;
   public:
      TProcess (void);
      HAB getAnchorBlock (void);
      HMQ getMsgQue (void);
      virtual const char *getClassName(void);

};


#endif /* process.h */


