/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: process.cc 1.2 1995/08/13 03:21:12 teb Exp $ */


#include "process.h"


//-------------------------------------------------------------------
//   TProcess
TProcess::TProcess (void)
{
   hAnchrBlk = WinInitialize (0);

   hMsgQue = WinCreateMsgQueue (hAnchrBlk,  0); 
}


//-------------------------------------------------------------------
//   getAnchorBlock
HAB TProcess::getAnchorBlock (void)
{
   return  hAnchrBlk;
}


//-------------------------------------------------------------------
//   getMsgQue
HMQ TProcess::getMsgQue (void)
{
   return  hMsgQue;
}


//-------------------------------------------------------------------
//  getClassName
const char *TProcess::getClassName(void)
{
   return "TProcess";
}

