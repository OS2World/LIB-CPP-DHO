/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: listbox.h 1.3 1995/08/13 03:21:12 teb Exp $ */

#ifndef __LISTBOX_H__
#define __LISTBOX_H__



#include<winbase.h>
#include<control.h>



//-------------------------------------------------
//   TListBase -- base class for TListBox,
//                TComboBox, and TPullDownList

class TListBase : public TControl
{
   protected:
      TListBase(TWinBase *parent, ULONG resource);
      virtual ~TListBase();

   public:
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


//-----------------------------------------------
//  TListBox
class TListBox: public TListBase
{
   public:
      TListBox(TWinBase *parent, ULONG resource);
      TListBox(TWinBase *parent, ULONG id, LONG xPos, LONG yPos,
                  LONG xWidth, LONG yHeight, BOOL adjustPos);
      TListBox(TWinBase *parent, ULONG id, LONG xPos, LONG yPos,
                  LONG xWidth, LONG yHeight, BOOL adjutsPos, 
                  char **items, LONG numItems);

      virtual ~TListBox();

      virtual const char *getClassName();
};




//-----------------------------------------------
//  TComboBox
class TComboBox: public TListBase
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
};



//-----------------------------------------------
//  TPullDownList
class TPullDownList: public TListBase
{
   public:
      TPullDownList(TWinBase *parent, ULONG resource);
      TPullDownList(TWinBase *parent, ULONG id, LONG xPos, LONG yPos,
                  LONG xWidth, LONG yHeight, BOOL adjustPos);
      TPullDownList(TWinBase *parent, ULONG id, LONG xPos, LONG yPos,
                  LONG xWidth, LONG yHeight, BOOL adjutsPos, 
                  char **items, LONG numItems);

      virtual ~TPullDownList();

      virtual const char *getClassName();
};



//-----------------------------------------------
//  TPullDown
class TPullDown: public TListBase
{
   public:
      TPullDown(TWinBase *parent, ULONG resource);
      TPullDown(TWinBase *parent, ULONG id, LONG xPos, LONG yPos,
                  LONG xWidth, LONG yHeight, BOOL adjustPos);
      TPullDown(TWinBase *parent, ULONG id, LONG xPos, LONG yPos,
                  LONG xWidth, LONG yHeight, BOOL adjutsPos, 
                  char **items, LONG numItems);

      virtual ~TPullDown();

      virtual const char *getClassName();
};

#endif

