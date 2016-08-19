/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: mledtext.h 1.2 1995/08/13 03:21:12 teb Exp $ */

#ifndef __MLEDTEXT_H__
#define __MLEDTEXT_H__



#define INCL_WIN
#include<os2.h>

#include<object.h>
#include<winbase.h>
#include<control.h>


struct MultiLineEditTxtAttr 
{
   BOOL Border;
   BOOL horizScroll;
   BOOL vertScroll;
   BOOL ignoreTab;
   BOOL wordWrap;
   BOOL readOnly;
};



class TMultiLineEditText : public TControl
{

   public:
      TMultiLineEditText(TWinBase *parent, ULONG resource);
      TMultiLineEditText(TWinBase *parent, LONG x, LONG y, 
                         LONG cx, LONG cy, MultiLineEditTxtAttr fMLEattr);

      virtual ~TMultiLineEditText();

      virtual const char *getClassName();
      void getControlText(PCH buff, ULONG buf_len);
      void setControlText(PCH text, ULONG bytes);
      LONG getTextLength();
      void showControl();
      
};


#endif



























































