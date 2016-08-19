/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: radiobtn.h 1.2 1995/08/13 03:21:12 teb Exp $ */


#ifndef __RADIOBTN_H__
#define __RADIOBTN_H__



#include<object.h>
#include<winbase.h>
#include<control.h>


enum groupType {groupStart, inGroup, standAlone};


class TBaseButton : public TControl
{
   protected:
      ULONG Style;
      TBaseButton(TWinBase *parent, ULONG resource);
      TBaseButton(TWinBase *parent, groupType gt, 
                     char *text, ULONG cmdId,
                     ULONG x, ULONG y, ULONG cx, ULONG cy);
      ~TBaseButton();
   public:
      void clickButton();
      LONG getClickState();
      void setClickState(BOOL state);
      LONG getGroupSelection();
};



class TRadioButton : public TBaseButton
{
   public:
      TRadioButton(TWinBase *parent, ULONG resource);
      TRadioButton(TWinBase *parent, groupType gt, 
                     char *text, ULONG cmdId,
                     ULONG x, ULONG y, ULONG cx, ULONG cy);
      ~TRadioButton();
};



class TCheckBox : public TBaseButton
{
   public:
      TCheckBox(TWinBase *parent, ULONG resource);
      TCheckBox(TWinBase *parent, groupType gt, 
                     char *text, ULONG cmdId,
                     ULONG x, ULONG y, ULONG cx, ULONG cy);
      ~TCheckBox();
};


class T3StateButton : public TBaseButton
{
   public:
      T3StateButton(TWinBase *parent, ULONG resource);
      T3StateButton(TWinBase *parent, groupType gt,
                     char *text, ULONG cmdId,
                     ULONG x, ULONG y, ULONG cx, ULONG cy);
      ~T3StateButton();

};


#endif
