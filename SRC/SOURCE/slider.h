/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: slider.h 1.5 1995/08/13 03:21:12 teb Exp $ */


#ifndef __SLIDER_H__
#define __SLIDER_H__


#include<winbase.h>
#include<control.h>

enum Direction {horizontal, vertical};

class TSlider : public TControl
{

   public:
      TSlider(TWinBase *parent, ULONG resource);
      TSlider(TWinBase *parent, Direction dir, SHORT x, SHORT y, 
               SHORT width, SHORT height);
      virtual ~TSlider();

      virtual const char *getClassName();

      void placeAtTick(SHORT no);
      void tickSize(SHORT pix);
      void setTickText(SHORT tick, CHAR *text);

      ULONG getSliderPos();

      void DetentShaftCenter();
};

#endif

