/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: pushbtn.cc 1.2 1995/08/13 03:21:12 teb Exp $ */


#include"pushbtn.h"


//-------------------------------------------------------------------
//   TPushButton
TPushButton::TPushButton(TWinBase *parent, ULONG resource):
   TControl(parent, resource)
{

}


//-------------------------------------------------------------------
//   TPushButton
TPushButton::TPushButton(TWinBase *parent, char *text, ULONG id, LONG xPos, LONG yPos,
                  LONG xWidth, LONG yHeight):
     TControl(parent, 0)
{
   hwndControl = WinCreateWindow (
                      fParent->getHWND(),
                      WC_BUTTON,
                      (PSZ)text,
                      WS_VISIBLE | BS_PUSHBUTTON,
                      xPos, yPos, xWidth, yHeight,
                      fParent->getHWND(),
                      HWND_TOP,
                      id, (PVOID)NULL, (PVOID)NULL);

}

//-------------------------------------------------------------------
//   ~TPushButton
TPushButton::~TPushButton()
{

}


//-------------------------------------------------------------------
//   getClassName
const char *TPushButton::getClassName()
{
   return "TPushButton";
}
