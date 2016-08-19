/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: static.h 1.2 1995/08/13 03:21:12 teb Exp $ */


#ifndef __STATIC_H__
#define __STATIC_H__


#include<winbase.h>
#include<control.h>

//-------------------------------------------------------------------
//  TStaticBase
class TStaticBase :  public TControl
{
   protected:
      ULONG classStyle;
      ULONG fx, fy, cx, cy;
      char *text;

      void initC();
      TStaticBase(TWinBase *parent, ULONG resource);
      TStaticBase(TWinBase *parent);
};


//-------------------------------------------------------------------
//  TStaticText
class TStaticText : public TStaticBase
{
   public:
      TStaticText(TWinBase *Parent, char *text, 
                   ULONG x, ULONG y, ULONG width, ULONG height);
      TStaticText(TWinBase *parent, ULONG resource);
      virtual const char *getClassName();
      void setText(char *text);
};



//-------------------------------------------------------------------
//  TBitmap
class TBitmap : public TStaticBase
{
   public:
      TBitmap(TWinBase *Parent, ULONG id, ULONG x, ULONG y,
				  ULONG width, ULONG height);
      TBitmap(TWinBase *parent, ULONG resource);
      virtual const char *getClassName();
};




//-------------------------------------------------------------------
//  TGroupBox
class TGroupBox : public TStaticBase
{
   public:
      TGroupBox(TWinBase *Parent, ULONG x, ULONG y,
					 ULONG width, ULONG height);
      TGroupBox(TWinBase *parent, ULONG resource);
      virtual const char *getClassName();
};



//-------------------------------------------------------------------
//  TIcon 
class TIcon : public TStaticBase
{
    public:
      TIcon(TWinBase *Parent, ULONG id, ULONG x, ULONG y,
				ULONG width, ULONG height);
      TIcon(TWinBase *parent, ULONG resource);
      virtual const char *getClassName();
};





#endif /* static.h */

