/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: window.cc 1.17 1995/08/29 18:20:14 teb Exp $ */


#include"window.h"
#include"applicat.h"
#include<os2.h>


BOOL TWindow::fInitialized = FALSE;



TWindow *temp_win_THIS;

MRESULT EXPENTRY DHOWndProc(HWND hWnd,ULONG iMessage, MPARAM mParam1, MPARAM mParam2);




//-------------------------------------------------------------------
//  BeginPaint
void TWindow::BeginPaint(HPS &hps, RECTL &rcl)
{
   hps = WinBeginPaint(hwnd, NULLHANDLE, &rcl);
}


//-------------------------------------------------------------------
//  EndPaint
void TWindow::EndPaint(HPS hps)
{
   WinEndPaint(hps);
}



//-------------------------------------------------------------------
//  paintWindow
void TWindow::paintWindow(HPS ps, RECTL rcl)
{

}

//-------------------------------------------------------------------
//  WinGetPS
HPS TWindow::GetPS()
{
   return WinGetPS(hwnd);
}


//-------------------------------------------------------------------
//  WinReleasePS
void TWindow::ReleasePS(HPS hps)
{
   ReleasePS(hps);
}

//-------------------------------------------------------------------
//  getWindowProc
PFNWP TWindow::getWindowProc()
{
   return (PFNWP)DHOWndProc;
}

//-------------------------------------------------------------------
//  TWindow
TWindow::TWindow(ULONG id, TWinBase *parent):
   TWinBase(id)
{
   temp_win_THIS = this;
   fParent = parent;
   fId = id;
   oldWndProc = (PFNWP)NULL;
}


//-------------------------------------------------------------------
//  ~TWindow
TWindow::~TWindow()
{

}


//-------------------------------------------------------------------
//  Init
BOOL TWindow::init()
{
   HWND hwndOwner;

   if (!fParent)
      hwndOwner = HWND_DESKTOP;
   else
      hwndOwner = fParent->getHWND();

   if (!fInitialized)
      Register();

   hwnd = WinCreateWindow (hwndOwner,(PSZ)WC_DHOWINDOW, NULL,
               0 ,0,0,0,0,hwndOwner,HWND_BOTTOM, fId ,NULL, NULL);

   return (hwnd!=(HWND)NULL);
}


//-------------------------------------------------------------------
//  ShowWindow
void TWindow::ShowWindow()
{ 
   WinShowWindow(hwnd,TRUE);
}
     

//-------------------------------------------------------------------
//  HideWindow
void TWindow::HideWindow()
{ 
   WinShowWindow(hwnd,FALSE);
}


//-------------------------------------------------------------------
//  Wpdate
BOOL TWindow::Update(void)
{ 
   return WinUpdateWindow(hwnd);
}


//-------------------------------------------------------------------
//  WndProc
MRESULT TWindow::WndProc(HWND hWnd, ULONG Message, MPARAM mParam1, MPARAM mParam2 )
{
   WinMsg msg;
   msg.hwnd = hWnd;
   msg.msg = Message;
   msg.mp1 = mParam1;
   msg.mp2 = mParam2;

   switch(Message)
   {
      case WM_ERASEBACKGROUND:
         return (MRESULT)TRUE;

      case WM_COMMAND:
            doCommand(msg);
            return (MRESULT)FALSE;
         break;
      case WM_CONTROL:
            doControl(msg);
            return (MRESULT)FALSE;
         break;
      case WM_HELP:
            doHelp(msg);
            return (MRESULT) FALSE;
            break;
      case WM_DESTROY:
            doDestroy(msg);
            return (MRESULT)FALSE;
         break;
      case WM_CLOSE:
            doClose(msg);
            return (MRESULT)FALSE;
         break;
      case WM_ACTIVATE:
            doActivate(msg);
            return (MRESULT)FALSE;
         break;
      case WM_CHAR:
            doChar(msg);
            return (MRESULT)FALSE;
          break;
      case WM_BUTTON1UP:
              doButton1Up(msg);
              return (MRESULT)FALSE;
           break;
      case WM_BUTTON1DOWN:
              doButton1Down(msg);
              return (MRESULT)FALSE;
           break;
      case WM_BUTTON1DBLCLK:
              doButton1DblClick(msg);
              return (MRESULT)FALSE;
           break;
       case WM_BUTTON2UP:
              doButton2Up(msg);
              return (MRESULT)FALSE;
           break;
       case WM_BUTTON2DOWN:
              doButton2Down(msg);
              return (MRESULT)FALSE;
           break;
       case WM_BUTTON2DBLCLK:
              doButton1DblClick(msg);
              return (MRESULT)FALSE;
           break;
       case WM_BUTTON3UP:
              doButton3Up(msg);
              return (MRESULT)FALSE;
           break;
      case WM_BUTTON3DOWN:
              doButton3Down(msg);
              return (MRESULT)FALSE;
           break;
       case WM_BUTTON3DBLCLK:
              doButton3DblClick(msg);
              return (MRESULT)FALSE;
           break;
      case WM_PAINT:
           doPaint(msg);
           return (MRESULT)FALSE;
         break;
      case WM_ADJUSTWINDOWPOS:
            doAdjustWindowPos(msg);
            return (MRESULT)FALSE;
         break;
      case WM_TIMER:
            doTimer(msg);
            return (MRESULT)FALSE;
      case WM_SIZE:
            doSize(msg);
            return (MRESULT)FALSE;
      case WM_SETFOCUS:
            doSetFocus(msg);
            return (MRESULT)FALSE;

      default:
         return WinDefWindowProc(hWnd, Message, mParam1, mParam2);
   }
   return (MRESULT)WinDefWindowProc(hWnd, Message, mParam1, mParam2);
}


//-------------------------------------------------------------------
//  getClassName
const char *TWindow::getClassName(void)
{
   return "TWindow";
}


//-------------------------------------------------------------------
//  Register
void TWindow::Register()
{
   BOOL reg;

   HAB anchor_block = Application->getAnchorBlock();
   if (!fInitialized)
   {
     reg = WinRegisterClass(anchor_block, (PSZ)WC_DHOWINDOW,
                    (PFNWP)DHOWndProc, CS_SIZEREDRAW | CS_SYNCPAINT
                    ,sizeof(TWindow));

#ifdef DEBUG
     if (!reg)
         WinMessageBox(HWND_DESKTOP,HWND_DESKTOP, 
            (PSZ)"Window class not registered correctly!!",
            (PSZ)"Warning",0, MB_MOVEABLE | MB_CANCEL ); 
#endif     
     fInitialized = reg;
   }

}

//-------------------------------------------------------------------
//  
void TWindow::setTitle(char *title)
{
   WinSetWindowText(getHWND(), (PSZ)title);
}

//-------------------------------------------------------------------
//  doCommand
void TWindow::doCommand(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}



//-------------------------------------------------------------------
//  doControl
void TWindow::doControl(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}

//-------------------------------------------------------------------
//  doDestroy
void TWindow::doDestroy(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}


//-------------------------------------------------------------------
//  doClose
void TWindow::doClose(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}

//-------------------------------------------------------------------
//  doPaint
void TWindow::doPaint(WinMsg wm)
{
   RECTL rcl;
   HPS ps;

   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
   {
      ps = WinBeginPaint(wm.hwnd, NULLHANDLE, &rcl);
      paintWindow(ps, rcl);
      WinEndPaint(ps);
   }
}


//-------------------------------------------------------------------
//  doSize
void TWindow::doSize(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
   {
      height = SHORT1FROMMP(wm.mp2);
      width  = SHORT2FROMMP(wm.mp2);
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   }
}




//-------------------------------------------------------------------
//  doRealizePallette
void TWindow::doRealizePallette(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}




//-------------------------------------------------------------------
//  doHelp
void TWindow::doHelp(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}


//-------------------------------------------------------------------
//  doActivate
void TWindow::doActivate(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}


//-------------------------------------------------------------------
//  doChar
void TWindow::doChar(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}

//-------------------------------------------------------------------
//  do
void TWindow::doButton1Up(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}

//-------------------------------------------------------------------
//  do
void TWindow::doButton1Down(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}


//-------------------------------------------------------------------
//  do
void TWindow::doButton1DblClick(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}

//-------------------------------------------------------------------
//  do
void TWindow::doButton2Up(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}


//-------------------------------------------------------------------
//  do
void TWindow::doButton2Down(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}


//-------------------------------------------------------------------
//  do
void TWindow::doButton2DblClick(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}


//-------------------------------------------------------------------
//  do
void TWindow::doButton3Up(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}


//-------------------------------------------------------------------
//  do
void TWindow::doButton3Down(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}


//-------------------------------------------------------------------
//  do
void TWindow::doButton3DblClick(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}



//-------------------------------------------------------------------
//  do
void TWindow::doAdjustWindowPos(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}



//-------------------------------------------------------------------
//  doTimer
void TWindow::doTimer(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}




//-------------------------------------------------------------------
//  doTimer
void TWindow::doSetFocus(WinMsg wm)
{
   if (oldWndProc)
      (*oldWndProc)(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
   else
      WinDefWindowProc(wm.hwnd, wm.msg, wm.mp1, wm.mp2);
}



//-------------------------------------------------------------------
//  DHOWndProc
MRESULT EXPENTRY DHOWndProc(HWND hWnd,ULONG iMessage,
    MPARAM mParam1, MPARAM mParam2)
{
 
    TWindow *pWindow = (TWindow *)WinQueryWindowULong(hWnd,0);

    if (pWindow == 0) 
    {
        if (iMessage == WM_CREATE) 
        {
           pWindow = temp_win_THIS;
            WinSetWindowULong(hWnd,0,(ULONG)pWindow);
            return pWindow->WndProc(hWnd,iMessage,mParam1,mParam2);
        } 
        else
            return WinDefWindowProc(hWnd,iMessage,mParam1,mParam2);
    } 
    else
        return pWindow->WndProc(hWnd,iMessage,mParam1,mParam2);
}








