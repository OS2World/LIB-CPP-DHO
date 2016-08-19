/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: moddlog.cc 1.8 1995/08/21 05:59:24 teb Exp $ */

#include"moddlog.h"
#include"pmutils.h"
TModalDialog *temp_MD_THIS = NULL;


//-------------------------------------------------------------------
//  TModalDialog
TModalDialog::TModalDialog(ULONG resource, TWinBase *owner, void *buffer):TWinBase(resource)
{
   fBuffer = buffer;
   fOwner = owner;
   temp_MD_THIS= this;
}


//-------------------------------------------------------------------
//  ~TModalDialog
TModalDialog::~TModalDialog()
{
   WinDestroyWindow(hwnd);
}
 


//----------------------------------------------------------------
//  Init
BOOL TModalDialog::init()
{
   HWND ownerHwnd = HWND_DESKTOP;
   if (fOwner != NULL)
      ownerHwnd = fOwner->getHWND();

   hwnd = WinLoadDlg( HWND_DESKTOP,
			  ownerHwnd,
	                (PFNWP)ClientModDlogProc,
	                getResHMODULE(),
                        fResource,NULL);
   return (hwnd != (HWND)NULL);

}


//-------------------------------------------------------------------
//  Execute
ULONG TModalDialog::Execute()
{
   WinProcessDlg(hwnd);
   return ret_val;
}


//-------------------------------------------------------------------
//  getClassName
const char *TModalDialog::getClassName()
{
   return "TModalDialog";
}


//-------------------------------------------------------------------
//  DlogProc
MRESULT TModalDialog::DlogProc(HWND hWnd, ULONG Message, MPARAM mParam1, MPARAM mParam2 )
{
   WinMsg wm;
   wm.hwnd = hWnd;
   wm.msg = Message;
   wm.mp1 = mParam1;
   wm.mp2 = mParam2;

   switch (Message)
   {
      case WM_COMMAND:
         doCommand(wm);
         return (MRESULT)FALSE;
      break;
         
      case WM_CONTROL:
         doControl(wm);
         return (MRESULT)TRUE;
      break;
  
      default:
         return WinDefDlgProc(hWnd, Message, mParam1, mParam2);
   }
   return (MRESULT)FALSE;
}


//-------------------------------------------------------------------
//  doCommand
void TModalDialog::doCommand(WinMsg wm)
{
   SHORT command = SHORT1FROMMP(wm.mp1);
   if (command == DID_OK)
   {
    ret_val = DID_OK;
    if (doOK())
      WinDismissDlg(hwnd,1);
    }
    else if (command == DID_CANCEL) 
    {
       ret_val = DID_CANCEL;
       doCancel();
       WinDismissDlg(hwnd,1);
   }

}


//-------------------------------------------------------------------
//  doCommand
void TModalDialog::doControl(WinMsg wm)
{
   WinDefDlgProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}




//-------------------------------------------------------------------
//  doOk
SHORT TModalDialog::doOK(void)
{
   SetData();
   return 1;
}


//-------------------------------------------------------------------
//  SetData
void TModalDialog::SetData()
{

}


//-------------------------------------------------------------------
//  doCancel
void TModalDialog::doCancel(void)
{

}


//-------------------------------------------------------------------
//  ClientModDlogProc
MRESULT EXPENTRY ClientModDlogProc (HWND hWnd,ULONG iMessage,
    MPARAM mParam1, MPARAM mParam2)
{
    
   WinMsg wm;
   wm.hwnd = hWnd;
   wm.msg = iMessage;
   wm.mp1 = mParam1;
   wm.mp2 = mParam2;

   TModalDialog *pDialog = (TModalDialog *)WinQueryWindowULong(hWnd,0);

   if (pDialog == 0) 
   {
      if (iMessage == WM_INITDLG)
      {
         pDialog = temp_MD_THIS;
         WinSetWindowULong(hWnd,0,(ULONG)pDialog);
         return pDialog->DlogProc(hWnd,iMessage,mParam1,mParam2);
      }
      else
         return WinDefDlgProc(hWnd,iMessage,mParam1,mParam2);
   } 
   else
      return pDialog->DlogProc(hWnd,iMessage,mParam1,mParam2);

}


