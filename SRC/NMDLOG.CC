/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: nmdlog.cc 1.9 1995/09/03 01:30:39 teb Exp $ */


#include"nmdlog.h"
#include"applicat.h"
#include"pmutils.h"

TNonModalDialog *temp_MDLGTHIS = NULL;


//-------------------------------------------------------------------
//  TNonModalDialog
TNonModalDialog::TNonModalDialog(ULONG resource):
      TWinBase(resource)
{
   temp_MDLGTHIS = this;
}


//-------------------------------------------------------------------
//  ~TNonModalDialog
TNonModalDialog::~TNonModalDialog()
{

}


//-------------------------------------------------------------------
//  Init
BOOL TNonModalDialog::init()
{
   SWP swp;
   BOOL ret;
   HAB hab = getApplication()->getAnchorBlock();

   hwnd = WinLoadDlg( HWND_DESKTOP,
                          HWND_DESKTOP,
                          (PFNWP)ClientDlogProc,
                          getResHMODULE(),
                          fResource,NULL);

   ret =  (hwnd != (HWND)NULL);

   if (ret)
   {
      WinQueryTaskSizePos(hab, 0, &swp);

      WinSetWindowPos(hwnd,(ULONG)NULL, swp.x,
                          swp.y, 0,0,SWP_SHOW | SWP_MOVE);
   }
   return ret; 
}


//-------------------------------------------------------------------
//  getClassName
const char *TNonModalDialog::getClassName(void)
{
   return "TNonModalDialog";
}


//-------------------------------------------------------------------
//  MakeFrame
BOOL TNonModalDialog::MakeFrame(void)
{
   hwnd = WinLoadDlg( HWND_DESKTOP,
                          HWND_DESKTOP,
                          (PFNWP)ClientDlogProc,
                          0,fResource,NULL);

   return (hwnd != (HWND)NULL);

}


//-------------------------------------------------------------------
//  doCommand
void TNonModalDialog::doCommand(WinMsg wm)
{
   WinDefDlgProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}


//-------------------------------------------------------------------
//  doCommand
void TNonModalDialog::doControl(WinMsg wm)
{
    WinDefDlgProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}


//-------------------------------------------------------------------
//  DlogProc
MRESULT TNonModalDialog::DlogProc(HWND hWnd, ULONG Message, MPARAM mParam1, MPARAM mParam2 )
{
   WinMsg wm;
   wm.hwnd = hWnd;
   wm.msg = Message;
   wm.mp1 = mParam1;
   wm.mp2 = mParam2;

   switch (Message)
   {
        case WM_CLOSE:
            WinPostMsg(hWnd, WM_QUIT, 0,0);
            return (MRESULT)FALSE;
        case WM_COMMAND:
            doCommand(wm);
            return (MRESULT)TRUE;
         break;
        case WM_CONTROL:
            doControl(wm);
         return (MRESULT)TRUE;
        default:
           return WinDefDlgProc(hWnd, Message,mParam1, mParam2);
        break;
   }
   return (MRESULT)FALSE;
}


//-------------------------------------------------------------------
//  ClientDlogProc
MRESULT EXPENTRY ClientDlogProc(HWND hWnd,ULONG iMessage,
       MPARAM mParam1, MPARAM mParam2)
{

    TNonModalDialog *pDialog = (TNonModalDialog *)WinQueryWindowULong(hWnd,0);

    if (pDialog == 0)
    {
        if (iMessage == WM_INITDLG)
        {
            pDialog = temp_MDLGTHIS;
            WinSetWindowULong(hWnd,0,(ULONG)pDialog);
            return pDialog->DlogProc(hWnd,iMessage,mParam1,mParam2);
        }
        else
            return WinDefDlgProc(hWnd,iMessage,mParam1,mParam2);
    }
    else
        return pDialog->DlogProc(hWnd,iMessage,mParam1,mParam2);
}

