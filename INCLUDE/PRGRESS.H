/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: prgress.h 1.4 1995/08/26 22:51:59 teb Exp $ */


#ifndef __PRGRESS_H__
#define __PRGRESS_H__

#define INCL_WIN
#define INCL_GPI
#include<os2.h>

#include<window.h>

/*****************************************************************
 *   this class implements a simple progress meter window        *
 *   control.                                                    *
 *****************************************************************/

class TProgressBar : public TWindow
{
   char progStr[50];
   ULONG perDone; 
   ULONG x, y, cx, cy;
   ULONG bg, fg, brdr;
   public:
      TProgressBar(ULONG id, TWinBase *parent, ULONG x, ULONG y,
                   ULONG cx, ULONG cy);
      virtual ~TProgressBar();
      virtual BOOL init();
      virtual void paintWindow(HPS ps, RECTL rcl);
  
      void setPercentDone(LONG percent);     
      ULONG getPercentDone();

      void setBackground(ULONG clr_index);
      void setForeground(ULONG clr_index);
      void setBorder(ULONG clr_index);
};

#endif
