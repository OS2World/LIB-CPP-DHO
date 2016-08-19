/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: static.cc 1.2 1995/08/13 03:21:12 teb Exp $ */


#include"static.h"
#include<stdio.h>


//-----------------------------------------------------
//   TStaticBase
TStaticBase::TStaticBase(TWinBase *parent, ULONG resource):
   TControl(parent, resource)
{

}

//-----------------------------------------------------
//   TStaticBase
TStaticBase::TStaticBase(TWinBase *parent):
   TControl(parent)
{

}


//-----------------------------------------------------
//   initC
void TStaticBase::initC()
{
   hwndControl = WinCreateWindow(
            fParent->getHWND(),
            WC_STATIC,
            (PSZ)text,
            WS_VISIBLE | classStyle,
            fx, fy, cx, cy,
            fParent->getHWND(),
            HWND_TOP,
            fResource,
            NULL, NULL);
}



//-----------------------------------------------------
//   TStaticText
TStaticText::TStaticText(TWinBase *Parent, char *text,
                   ULONG x, ULONG y, ULONG width, ULONG height):
   TStaticBase(Parent)
{
   fx = x;
   fy = y;
   cx = width;
   cy = height;
   this->text = text;
   classStyle = SS_TEXT;
   initC();
}


//-----------------------------------------------------
//   TStaticText
TStaticText::TStaticText(TWinBase *parent, ULONG resource):
   TStaticBase(parent, resource)
{

}


//-----------------------------------------------------
//   getClassName
const char *TStaticText::getClassName()
{
   return "TStaticText";
}

void TStaticText::setText(char *text)
{
   WinSetWindowText(hwndControl, (PSZ)text);
}


//-----------------------------------------------------
//   TBitmap
TBitmap::TBitmap(TWinBase *Parent, ULONG id, ULONG x, ULONG y, ULONG width, ULONG height):
   TStaticBase(Parent)
{
   char buf[50];
   fx = x;
   fy = y;
   cx = width;
   cy = height;

   sprintf(buf, "#%ld", id);
   text = buf;
   classStyle = SS_BITMAP;

   initC();
}


//-----------------------------------------------------
//   TBitmap
TBitmap::TBitmap(TWinBase *parent, ULONG resource):
   TStaticBase(parent, resource)
{

}


//-----------------------------------------------------
//   TBitmap
const char *TBitmap::getClassName()
{
   return "TBitmap";
}



//-----------------------------------------------------
//   TGroupBox
TGroupBox::TGroupBox(TWinBase *Parent, ULONG x, ULONG y, ULONG width, ULONG height):
   TStaticBase(Parent)
{
   fx = x;
   fy = y;
   cx = width;
   cy = height;
   text = NULL;
   classStyle = SS_GROUPBOX;

   initC();
}
 

//-----------------------------------------------------
//   TGroupBox
TGroupBox::TGroupBox(TWinBase *parent, ULONG resource):
   TStaticBase(parent, resource)
{


}


//-----------------------------------------------------
//   getClassName
const char *TGroupBox::getClassName()
{
   return "TGroupBox";
}



//-----------------------------------------------------
//   TIcon
TIcon::TIcon(TWinBase *Parent, ULONG id, ULONG x, ULONG y, ULONG width, ULONG height):
   TStaticBase(Parent)
{
   char buf[50];

   fx = x;
   fy = y;
   cx = width;
   cy = height;
   sprintf(buf, "#%ld", id);
   text = buf;
   classStyle = SS_ICON;

   initC();
}


//-----------------------------------------------------
//   TIcon
TIcon::TIcon(TWinBase *parent, ULONG resource):
   TStaticBase(parent, resource)
{

}


//-----------------------------------------------------
//   getClassName
const char *TIcon::getClassName()
{
   return "TIcon";
}


