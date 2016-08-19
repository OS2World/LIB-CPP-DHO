/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: moddlog.h 1.6 1995/08/21 05:28:51 teb Exp $ */

#ifndef __MODDLOG_H__
#define __MODDLOG_H__

#include<winbase.h>

class TModalDialog : public TWinBase
{
   protected:
      TWinBase *fOwner;
      void *fBuffer;
      ULONG ret_val;
   public:
      TModalDialog(ULONG resource, TWinBase *owner, void *buffer);
      virtual ~TModalDialog();
      ULONG Execute();
      virtual BOOL init();
      virtual MRESULT DlogProc(HWND hWnd, ULONG Message,
										 MPARAM mParam1, MPARAM mParam2 );

      virtual void doCommand(WinMsg wm);
      virtual void doControl(WinMsg wm);
      virtual SHORT doOK(void);
      virtual void doCancel(void);

      virtual void SetData();

      virtual const char *getClassName();
};


MRESULT EXPENTRY ClientModDlogProc(HWND hWnd,ULONG iMessage,
												MPARAM mParam1, MPARAM mParam2);


#endif

