/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: mledtext.cc 1.3 1995/08/13 03:21:12 teb Exp $ */


#include <mledtext.h>

//--------------------------------------------------------------
//  TMultiLineEditText
TMultiLineEditText::TMultiLineEditText(TWinBase *parent, ULONG resource):
   TControl(parent, resource)

{
   
}


//--------------------------------------------------------------
//  TMultiLineEditText
TMultiLineEditText::TMultiLineEditText(TWinBase *parent, LONG x, LONG y, 
                         LONG cx, LONG cy, MultiLineEditTxtAttr fMLEattr):
   TControl(parent)
{
   ULONG style = WS_VISIBLE;

   if (fMLEattr.Border)
      style |= MLS_BORDER;
   if (fMLEattr.horizScroll)
      style |= MLS_HSCROLL;
   if (fMLEattr.vertScroll)
      style |= MLS_VSCROLL;
   if (fMLEattr.ignoreTab)
      style |= MLS_IGNORETAB;
   if (fMLEattr.wordWrap)
      style |= MLS_WORDWRAP;
   if (fMLEattr.readOnly)
      style |= MLS_READONLY;

   hwndControl = WinCreateWindow(
             parent->getHWND(),
             WC_MLE,
             (PSZ)NULL,
             style,
             x,y, cx, cy,
             parent->getHWND(), 
             HWND_TOP, 
             0,             
             NULL, NULL);
}



//--------------------------------------------------------------
//  ~TMultiLineEditText
TMultiLineEditText::~TMultiLineEditText()
{

}



//--------------------------------------------------------------
//   getClassName
const char *TMultiLineEditText::getClassName()
{
   return "TMultiLineEditText";
}



//--------------------------------------------------------------
//  getControlText
void TMultiLineEditText::getControlText(PCH buff, ULONG buf_len)
{
   IPT offset = 0;
   WinSendMsg(hwndControl, MLM_EXPORT,
              MPFROMP(&offset), MPFROMP(buf_len));
}


//--------------------------------------------------------------
// setControlText
void TMultiLineEditText::setControlText(PCH text, ULONG bytes)
{
   IPT offset = 0;
    WinSendMsg(hwndControl, MLM_IMPORT, 
               MPFROMP(&offset), MPFROMP(&bytes));
}


//--------------------------------------------------------------
//  getTextLength
LONG TMultiLineEditText::getTextLength()
{
   return (LONG)WinSendMsg(hwndControl, MLM_QUERYFORMATTEXTLENGTH,
              MPFROMLONG(0), MPFROMLONG((-1)));
}


//--------------------------------------------------------------
//   showControl
void TMultiLineEditText::showControl()
{
   WinShowWindow(hwndControl, TRUE);
}
