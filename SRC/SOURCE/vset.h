/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: vset.h 1.7 1995/08/26 23:50:45 teb Exp $ */

#ifndef __VSET_H__
#define __VSET_H__

#define INCL_WIN
#include<os2.h>
#include<pmwrap.h>


enum setType {colors, bitmaps, icon, text};


struct ValSetAttrib
{
   setType items;
   BOOL itemBorder;
   BOOL setBorder;
   BOOL scaleItems;
   SHORT x;
   SHORT y;
   SHORT width;
   SHORT height;
};


class TValueSet: public TWinBase
{
      USHORT fRows, fCols;
      VSCDATA vscData;
      ULONG ulVSetStyle;
      ULONG fData;			 
      SHORT fX, fY, fcX, fcY;
      ULONG fId;
      TWinBase *fParent;
    
   public:
      ValSetAttrib fVSetAttr;
      TValueSet(ULONG id, TWinBase *parent, USHORT rows, USHORT cols);
      ~TValueSet();
      USHORT getNumRows();
      USHORT getNumCols();
      const char *getClassName(void);
      virtual BOOL init();
      void setItem(USHORT row, USHORT col, VOID *item);
      virtual MRESULT DoControl(MPARAM mParam1);
      void getSelection(SHORT &row, SHORT &col);
};


#endif









