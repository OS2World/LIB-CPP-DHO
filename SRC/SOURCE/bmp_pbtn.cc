/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: bmp_pbtn.cc 1.2 1995/08/13 03:21:12 teb Exp $ */


#include"bmp_pbtn.h"
#include"stdio.h"

//-------------------------------------------------------------------
//   TPushButton
TBmpPushButton::TBmpPushButton(TWinBase *parent, ULONG resource):
   TControl(parent, resource)
{

}


//-------------------------------------------------------------------
//   TPushButton
TBmpPushButton::TBmpPushButton(TWinBase *parent, ULONG bmpId, ULONG id, LONG xPos, LONG yPos,
                  LONG xWidth, LONG yHeight):
     TControl(parent, 0)
{
   char text[50];
   sprintf(text, "#%ld", bmpId);
   hwndControl = WinCreateWindow (
                      fParent->getHWND(),
                      WC_BUTTON,
                      (PSZ)text,
                      WS_VISIBLE | BS_PUSHBUTTON | BS_BITMAP,
                      xPos, yPos, xWidth, yHeight,
                      fParent->getHWND(),
                      HWND_TOP,
                      id, (PVOID)NULL, (PVOID)NULL);

}

//-------------------------------------------------------------------
//   ~TPushButton
TBmpPushButton::~TBmpPushButton()
{

}


//-------------------------------------------------------------------
//   getClassName
const char *TBmpPushButton::getClassName()
{
   return "TBmpPushButton";
}
