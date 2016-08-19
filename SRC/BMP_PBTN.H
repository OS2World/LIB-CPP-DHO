/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: bmp_pbtn.h 1.2 1995/08/13 03:21:12 teb Exp $ */

#ifndef __BMP_PBTN_H__
#define __BMP_PBTN_H__



#include<winbase.h>
#include<control.h>


class TBmpPushButton: public TControl
{
   public:
      TBmpPushButton(TWinBase *parent, ULONG resource);
      TBmpPushButton(TWinBase *parent, ULONG bmpId, ULONG id,
							LONG xPos, LONG yPos, LONG xWidth, LONG yHeight);
      virtual ~TBmpPushButton();

      virtual const char *getClassName();
};

#endif
