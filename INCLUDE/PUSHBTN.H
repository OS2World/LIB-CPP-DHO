/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: pushbtn.h 1.3 1995/08/13 03:21:12 teb Exp $ */


#ifndef __PUSHBTN_H__
#define __PUSHBTN_H__


#include<winbase.h>
#include<control.h>


class TPushButton: public TControl
{
   public:
      TPushButton(TWinBase *parent, ULONG resource);
      TPushButton(TWinBase *parent, char *text, ULONG id, LONG xPos,
						LONG yPos, LONG xWidth, LONG yHeight);
      virtual ~TPushButton();

      virtual const char *getClassName();
};

#endif
