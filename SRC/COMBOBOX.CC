/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: combobox.cc 1.2 1995/08/13 03:21:12 teb Exp $ */


#include"combobox.h"


//-------------------------------------------------------------------
//   TComboBox
TComboBox::TComboBox(TWinBase *parent, ULONG resource):
   TControl(parent, resource)
{

}

//-------------------------------------------------------------------
//   TComboBox
TComboBox::TComboBox(TWinBase *parent, ULONG id, LONG xPos, LONG yPos,
                  LONG xWidth, LONG yHeight, BOOL adjustPos):
   TControl(parent, 0)
{
   ULONG style= WS_VISIBLE;
   if (!adjustPos)
      style |= LS_NOADJUSTPOS;

   register int i;
   fResource = id;
   hwndControl = WinCreateWindow(
                fParent->getHWND(),
                WC_COMBOBOX,
                (PSZ)NULL,
                style,
                xPos, yPos,xWidth, yHeight,
                fParent->getHWND(),
                HWND_TOP,
                fResource,
                NULL, NULL);
}

//-------------------------------------------------------------------
//   TComboBox
TComboBox::TComboBox(TWinBase *parent, ULONG id, LONG xPos, LONG yPos,
                  LONG xWidth, LONG yHeight, BOOL adjustPos, char **items, LONG numItems):
   TControl(parent, 0)
{
   ULONG style= WS_VISIBLE;
   if (!adjustPos)
      style |= LS_NOADJUSTPOS;

   register int i;
   fResource = id;
   hwndControl = WinCreateWindow(
                fParent->getHWND(),
                WC_LISTBOX,
                (PSZ)NULL,
                style,
                xPos, yPos,xWidth, yHeight,
                fParent->getHWND(),
                HWND_TOP,
                fResource,
                NULL, NULL);

   if (hwndControl!=NULL)
   {
      for (i=0; i<numItems; i++)
         addItemAt(items[i],i);
   }

}



//-------------------------------------------------------------------
//   ~TComboBox
TComboBox::~TComboBox()
{

}


//-------------------------------------------------------------------
//   getClassName
const char *TComboBox::getClassName()
{
   return "TComboBox";
}


//-------------------------------------------------------------------
//   addItem
void TComboBox::addItemAt(char *item, SHORT at)
{
   WinInsertLboxItem(hwndControl, at, (PSZ)item);
}


//-------------------------------------------------------------------
//   deleteItem
void TComboBox::deleteItemAt (SHORT itemNo)
{
   short remaining;
      remaining = WinDeleteLboxItem(hwndControl, itemNo);
}


//-------------------------------------------------------------------
//   addItemFirst
void TComboBox::addItemFirst(char *item)
{
   addItemAt(item, 0);
}

//-------------------------------------------------------------------
//   addItemLast
void TComboBox::addItemLast(char *item)
{
   addItemAt(item, getNumItems());
}

//-------------------------------------------------------------------
//   deleteAll
void TComboBox::deleteAll()
{
   short num = getNumItems();
   while (num >=0)
   {
     WinDeleteLboxItem(hwndControl, 0);
     num--;
   }
}


//-------------------------------------------------------------------
//   getNumItems
SHORT TComboBox::getNumItems()
{
   return WinQueryLboxCount(hwndControl);
}

//-------------------------------------------------------------------
//   setItemText
void TComboBox::setItemText (char *text, SHORT item)
{
   WinSetLboxItemText(hwndControl,  item, (PSZ)text);
}


//-------------------------------------------------------------------
//   
SHORT TComboBox::getSelectedItem()
{
   return WinQueryLboxSelectedItem(hwndControl);
}


//-------------------------------------------------------------------
//   
ULONG TComboBox::getSelectedItemLength()
{
   return (ULONG)WinSendMsg(hwndControl, LM_QUERYITEMTEXTLENGTH,((MPARAM)(getSelectedItem())), (MPARAM)0);

} 

//-------------------------------------------------------------------
//   
ULONG TComboBox::getItemLength(SHORT at)
{
   return (ULONG)WinSendMsg(hwndControl, LM_QUERYITEMTEXTLENGTH,((MPARAM)(at)), (MPARAM)0);
}


//-------------------------------------------------------------------
// 
char *TComboBox::getItemAt(SHORT at)
{
   char *buf = NULL;
   ULONG size =  getItemLength(at);
   buf = new char[size+1];
   WinQueryLboxItemText(hwndControl, at, buf, size);
   return buf;
}
