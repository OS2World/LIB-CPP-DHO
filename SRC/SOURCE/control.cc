/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: control.cc 1.5 1995/08/13 03:21:12 teb Exp $ */

#include"control.h"

//-------------------------------------------------------------------
//   TControl
TControl::TControl(TWinBase *parent, ULONG resource)
{
   fParent = parent;
   fResource = resource;
   hwndControl = WinWindowFromID( fParent->getHWND() , fResource);
}


//-------------------------------------------------------------------
//   TControl
TControl::TControl(TWinBase *parent)
{
   fParent = parent;
   fResource = 0;
   hwndControl = (HWND)NULL;
}


//-------------------------------------------------------------------
//   ~TControl
TControl::~TControl()
{

}


//-------------------------------------------------------------------
//   SendMessage
MRESULT TControl::SendMessage(ULONG ul, MPARAM mp1, MPARAM mp2)
{
   return WinSendMsg( hwndControl, ul, mp1, mp2);
}


//-------------------------------------------------------------------
//   getClassName
const char *TControl::getClassName()
{
   return "TControl";
}

//-------------------------------------------------------------------
//   showControl
void TControl::showControl()
{
   WinShowWindow(hwndControl, TRUE);
}


//-------------------------------------------------------------------
//   enable
void TControl::enable()
{
   WinEnableWindow(hwndControl, TRUE);
}


//-------------------------------------------------------------------
//   disable
void TControl::disable()
{
   WinEnableWindow(hwndControl, FALSE);
}
