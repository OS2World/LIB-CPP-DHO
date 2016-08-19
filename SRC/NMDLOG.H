/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: nmdlog.h 1.7 1995/08/21 05:32:14 teb Exp $ */


#ifndef __NMDLOG_H__
#define __NMDLOG_H__

#include<winbase.h>

class TNonModalDialog : public TWinBase
{

   public:
      TNonModalDialog(ULONG resource);
      virtual ~TNonModalDialog();
      virtual BOOL init();
      virtual const char *getClassName(void);
      virtual BOOL MakeFrame(void);
      virtual void doCommand(WinMsg wm);
      virtual void doControl(WinMsg wm);

      MRESULT DlogProc(HWND hWnd, ULONG Message,
							  MPARAM mParam1, MPARAM mParam2 );

};

MRESULT EXPENTRY ClientDlogProc(HWND hWnd,ULONG iMessage,
                                MPARAM mParam1, MPARAM mParam2);


#endif

