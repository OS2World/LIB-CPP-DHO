/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: edittext.h 1.5 1995/08/13 03:21:12 teb Exp $ */

#ifndef __EDITTEXT_H__
#define __EDITTEST_H__



#define INCL_WIN
#include<os2.h>

#include<object.h>
#include<winbase.h>
#include<control.h>


struct EditTxtAttr 
{
   BOOL anyChar;
   BOOL autoScroll;
   BOOL autoTab;
   justification lcr;
   BOOL margin;
   BOOL readOnly;
   BOOL unreadable;
   PSZ initialText;
   LONG charLimit;
   LONG minSel;
   LONG maxSel;
};



class TEditText: public TControl
{
      HWND hwndEntryField;     // is non-null if not constructed via resource.
   public:
      TEditText(TWinBase *parent, ULONG resource);
      TEditText(TWinBase *parent, EditTxtAttr *etr, LONG xPos, LONG yPos, 
                  LONG xWidth, LONG yHeight);
      virtual ~TEditText();

      virtual const char *getClassName();
      void getControlText(PCH buff, ULONG buf_len);
      void setControlText(PCH text);
      LONG getTextLength();
      void showControl();
};


#endif

