/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: spinbtn.h 1.4 1995/08/13 03:21:12 teb Exp $ */

#ifndef __SPINBTN_H__
#define __SPINBTN_H__



#include<winbase.h>
#include<control.h>

struct SpinBtnAttr
{
   justification lcr;
   BOOL numberic;
   BOOL fastspin;
   BOOL noBorder;
   BOOL readOnly;
   BOOL padZeros;
};



class TSpinButton: public TControl
{
   protected:
      LONG fMin;
      LONG fMax;
   public:
      TSpinButton(TWinBase *parent, ULONG resource, LONG min, LONG max);
      TSpinButton(TWinBase *parent, SpinBtnAttr *etr, LONG xPos, LONG yPos,
                  LONG xWidth, LONG yHeight, LONG min, LONG max);
      virtual ~TSpinButton();

      virtual const char *getClassName();
      void setCurrentValue(LONG cVal);
      LONG getCurrentValue();
      void setLimits(LONG min, LONG max);
};


#endif

