/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: combobox.h 1.2 1995/08/13 03:21:12 teb Exp $ */

#ifndef __SPINBTN_H__
#define __SPINBTN_H__




#include<winbase.h>
#include<control.h>


class TComboBox: public TControl
{
   public:
      TComboBox(TWinBase *parent, ULONG resource);
      TComboBox(TWinBase *parent, ULONG id, LONG xPos, LONG yPos,
                  LONG xWidth, LONG yHeight, BOOL adjustPos);
      TComboBox(TWinBase *parent, ULONG id, LONG xPos, LONG yPos,
                  LONG xWidth, LONG yHeight, BOOL adjutsPos,
					   char **items, LONG numItems);
      virtual ~TComboBox();

      virtual const char *getClassName();
      void addItemAt(char *item, SHORT at);
      void addItemFirst(char *item);
      void addItemLast(char *item);
      void deleteItemAt (SHORT itemNo);
      void deleteAll();
      SHORT getNumItems();
      void setItemText (char *text, SHORT item);
      SHORT getSelectedItem();
      char *getItemAt(SHORT at);
      ULONG getItemLength(SHORT at);
      ULONG getSelectedItemLength();
};


#endif
