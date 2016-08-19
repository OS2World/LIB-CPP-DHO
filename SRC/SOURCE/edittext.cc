/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: edittext.cc 1.5 1995/08/13 03:21:12 teb Exp $ */


#include"edittext.h"
#include"window.h"

//-------------------------------------------------------------------
//   TEditText
TEditText::TEditText (TWinBase *parent, ULONG resource): TControl( parent, resource)
{
   hwndEntryField = NULL;
}


//-------------------------------------------------------------------
//   TEditText
TEditText::TEditText(TWinBase *parent, EditTxtAttr *etr, LONG xPos, LONG yPos,
                  LONG xWidth, LONG yHeight): TControl(parent)
{
   ENTRYFDATA efd;
   ULONG efStyle;

   efStyle = WS_VISIBLE;

//   if (etr->anyChar)
//      efStyle |= ES_ANY;
   if (etr->autoScroll)
      efStyle |= ES_AUTOSCROLL;
   if (etr->autoTab)
      efStyle |= ES_AUTOTAB;
   if (etr->lcr==left)
      efStyle |= ES_LEFT;
   else if (etr->lcr == center)
      efStyle |= ES_CENTER;
   else if (etr->lcr == right)
      efStyle |= ES_RIGHT;
   if (etr->margin)
      efStyle |= ES_MARGIN;
   if (etr->readOnly)
      efStyle |= ES_READONLY;
   if (etr->unreadable)
      efStyle |= ES_UNREADABLE;


   efd.cb = sizeof(ENTRYFDATA);
   efd.cchEditLimit=etr->charLimit;
   efd.ichMinSel = etr->minSel;
   efd.ichMaxSel = etr->maxSel;

   hwndEntryField = WinCreateWindow(
      parent->getHWND(),
      WC_ENTRYFIELD,
      etr->initialText,
      efStyle,
      xPos, yPos,
      xWidth, yHeight,
      parent->getHWND(),
      HWND_TOP,
      0,
      &efd,
      NULL);
}

//-------------------------------------------------------------------
//   ~TEditText
TEditText::~TEditText()
{


}


//-------------------------------------------------------------------
//   TEditText
const char *TEditText::getClassName()
{
   return "TEditText";
}


//-------------------------------------------------------------------
//   getControlText
void TEditText::getControlText(PCH buff, ULONG buf_len)
{
   if (hwndEntryField==(HWND)NULL)
     WinQueryWindowText( WinWindowFromID( fParent->getHWND() , fResource) ,  buf_len, buff);
   else
      WinQueryWindowText(hwndEntryField, buf_len, buff);
 
}


//-------------------------------------------------------------------
//   setControlText
void TEditText::setControlText(PCH text)
{
   if (hwndEntryField==(HWND)NULL)
   {
      HWND tmp;
      tmp = WinWindowFromID( fParent->getHWND() , fResource);
      WinSetWindowText(tmp, text);
   }
   else
      WinSetWindowText(hwndEntryField, text);

}

//-------------------------------------------------------------------
//   getTextLength
LONG TEditText::getTextLength()
{
   long ret_val = 0;
   if (hwndEntryField==(HWND)NULL)
      ret_val =  WinQueryWindowTextLength(WinWindowFromID( fParent->getHWND() , fResource) );
   else
      ret_val =  WinQueryWindowTextLength(hwndEntryField);
   return ret_val;
}


//-------------------------------------------------------------------
//   showControl
void TEditText::showControl()
{
   WinShowWindow(hwndEntryField, TRUE);
}





