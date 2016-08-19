/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: control.h 1.5 1995/08/13 03:21:12 teb Exp $ */

#ifndef __CONTROL_H__
#define __CONTROL_H__



#include<object.h>
#include<winbase.h>

enum justification {left, center, right};


class TControl : public TObject
{
 
   protected:
      TWinBase *fParent;
      ULONG fResource;
      HWND hwndControl;
   public:
      TControl(TWinBase *parent, ULONG resource);
      TControl(TWinBase *parent);
      virtual ~TControl();
      MRESULT SendMessage(ULONG ul, MPARAM mp1, MPARAM mp2);

      virtual const char *getClassName();
      void showControl();
      
      void enable();

      void disable();
};

#endif  /* control.h */

