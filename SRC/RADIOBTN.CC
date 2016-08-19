/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: radiobtn.cc 1.2 1995/08/13 03:21:12 teb Exp $ */


#include"radiobtn.h"


//-------------------------------------------------------------------
//   TBaseButton
TBaseButton::TBaseButton(TWinBase *parent, ULONG resource):
   TControl(parent, resource)
{

}


//-------------------------------------------------------------------
//   TBaseButton
TBaseButton::TBaseButton(TWinBase *parent, groupType gt, char *text, ULONG cmdId,
                              ULONG x, ULONG y, ULONG cx, ULONG cy):
   TControl(parent)
{

}


//-------------------------------------------------------------------
//   ~TBaseButton
TBaseButton::~TBaseButton()
{

}



//-------------------------------------------------------------------
//   clickButton
void TBaseButton::clickButton()
{
   SendMessage(BM_CLICK, (MPARAM)NULL, (MPARAM) NULL);
}



//-------------------------------------------------------------------
//   getClickState
LONG TBaseButton::getClickState()
{
   return (LONG)SendMessage(BM_QUERYHILITE, NULL, NULL);
}



//-------------------------------------------------------------------
//   setClickState
void TBaseButton::setClickState(BOOL state)
{
    SendMessage(BM_SETHILITE, MPARAM(state), MPARAM(NULL));
}


//-------------------------------------------------------------------
//   getGroupSelection
LONG TBaseButton::getGroupSelection()
{
   return (LONG)SendMessage(BM_QUERYCHECKINDEX, MPARAM(NULL), MPARAM(NULL));
}



//-------------------------------------------------------------------
//   TRadioButton
TRadioButton::TRadioButton(TWinBase *parent, ULONG resource):
   TBaseButton(parent, resource)
{

}



//-------------------------------------------------------------------
//   TRadioButton
TRadioButton::TRadioButton(TWinBase *parent, groupType gt, char *text, ULONG cmdId,
                              ULONG x, ULONG y, ULONG cx, ULONG cy):
   TBaseButton(parent, gt, text, cmdId, x,  y, cx, cy)
{
   Style = BS_AUTORADIOBUTTON | WS_VISIBLE ;
   if ((gt == groupStart) || (gt == standAlone))
      Style |= WS_GROUP;

   hwndControl = WinCreateWindow(
                      fParent->getHWND(),
                      WC_BUTTON,
                      (PSZ)text,
                      Style,
                      x, y,cx,cy,
                      fParent->getHWND(),
                      HWND_TOP,
                      cmdId, (PVOID)NULL, (PVOID)NULL);

}


//-------------------------------------------------------------------
//   ~TRadioButton
TRadioButton::~TRadioButton()
{

}


//-------------------------------------------------------------------
//   TCheckBox
TCheckBox::TCheckBox(TWinBase *parent, ULONG resource):
   TBaseButton(parent, resource)
{

}



//-------------------------------------------------------------------
//   TCheckBox
TCheckBox::TCheckBox(TWinBase *parent, groupType gt, char *text, ULONG cmdId,
                              ULONG x, ULONG y, ULONG cx, ULONG cy):
   TBaseButton(parent, gt, text, cmdId, x,  y, cx, cy)
{
   Style = BS_CHECKBOX | WS_VISIBLE ;
 //  if ((gt == groupStart) || (gt == standAlone))
 //     Style |= WS_GROUP;

   hwndControl = WinCreateWindow(
                      fParent->getHWND(),
                      WC_BUTTON,
                      (PSZ)text,
                      Style,
                      x, y,cx,cy,
                      fParent->getHWND(),
                      HWND_TOP,
                      cmdId, (PVOID)NULL, (PVOID)NULL);

}


//-------------------------------------------------------------------
//   ~TCheckBox
TCheckBox::~TCheckBox()
{

}



//-------------------------------------------------------------------
//   T3StateButton
T3StateButton::T3StateButton(TWinBase *parent, ULONG resource):
   TBaseButton(parent, resource)
{

}

//-------------------------------------------------------------------
//   T3StateButton
T3StateButton::T3StateButton(TWinBase *parent, groupType gt,
                     char *text, ULONG cmdId,
                     ULONG x, ULONG y, ULONG cx, ULONG cy):
   TBaseButton(parent, gt, text, cmdId, x,  y, cx, cy)
{	
   Style = BS_AUTO3STATE | WS_VISIBLE ;
   if ((gt == groupStart) || (gt == standAlone))
      Style |= WS_GROUP;

   hwndControl = WinCreateWindow(
                      fParent->getHWND(),
                      WC_BUTTON,
                      (PSZ)text,
                      Style,
                      x, y,cx,cy,
                      fParent->getHWND(),
                      HWND_TOP,
                      cmdId, (PVOID)NULL, (PVOID)NULL);

}


//-------------------------------------------------------------------
//   ~T3StateButton
T3StateButton::~T3StateButton()
{

}
