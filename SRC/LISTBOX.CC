/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: listbox.cc 1.2 1995/08/13 03:21:12 teb Exp $ */


#include"listbox.h"

//----------------------------------------------------------------
//  TListBase
TListBase:: TListBase(TWinBase *parent, ULONG resource):
   TControl(parent, resource)
{

}
 


//----------------------------------------------------------------
//  ~TListBase
TListBase:: ~TListBase()
{

}


//-------------------------------------------------------------------
//   getClassName
const char *TListBase::getClassName()
{
   return "TListBase";
}



//-----------------------------------------------------------------
//   addItem
void TListBase::addItemAt(char *item, SHORT at)
{
   if(hwndControl)
      WinInsertLboxItem(hwndControl, at, (PSZ)item);
}


//-----------------------------------------------------------------
//  deleteItem
void TListBase::deleteItemAt (SHORT itemNo)
{
   WinSendMsg(hwndControl, LM_DELETEITEM, 
              MPFROMSHORT(itemNo), NULL);
}


//-----------------------------------------------------------------
// addItemFirst
void TListBase::addItemFirst(char *item)
{
   addItemAt(item, 0);
}

//-----------------------------------------------------------------
//   addItemLast
void TListBase::addItemLast(char *item)
{
   if (hwndControl)
      addItemAt(item, getNumItems());
}

//-----------------------------------------------------------------
//   deleteAll
void TListBase::deleteAll()
{
   if (hwndControl)
   {
      short num = getNumItems();
      while (num >=0)
      {
        WinDeleteLboxItem(hwndControl, 0);
        num--;
      }
   }
}


//-----------------------------------------------------------------
//   getNumItems
SHORT TListBase::getNumItems()
{
   return WinQueryLboxCount(hwndControl);
}

//-----------------------------------------------------------------
//   setItemText
void TListBase::setItemText (char *text, SHORT item)
{
   WinSetLboxItemText(hwndControl,  item, (PSZ)text);
}


//-----------------------------------------------------------------
//   getSelectedItem
SHORT TListBase::getSelectedItem()
{
   return WinQueryLboxSelectedItem(hwndControl);
}


//-----------------------------------------------------------------
//   getSelectedItemLength
ULONG TListBase::getSelectedItemLength()
{
   return (ULONG)WinSendMsg(hwndControl, 
                 LM_QUERYITEMTEXTLENGTH,
                 ((MPARAM)(getSelectedItem())), 
                 (MPARAM)0);
} 



//-----------------------------------------------------------------
//   getItemLength
ULONG TListBase::getItemLength(SHORT at)
{
   return (ULONG)WinSendMsg(hwndControl, 
                LM_QUERYITEMTEXTLENGTH,
                ((MPARAM)(at)), (MPARAM)0);
}



//-----------------------------------------------------------------
// getItemAt
char *TListBase::getItemAt(SHORT at)
{
   char *buf = NULL;
   ULONG size =  getItemLength(at);
   buf = new char[size+1];
   WinQueryLboxItemText(hwndControl, at, buf, size);
   return buf;
}




//-------------------------------------------------------------------
//   TListBox
TListBox::TListBox(TWinBase *parent, ULONG resource):
   TListBase(parent, resource)
{

}


//-------------------------------------------------------------------
//   TListBox
TListBox::TListBox(TWinBase *parent, ULONG id, LONG xPos, LONG yPos,
                  LONG xWidth, LONG yHeight, BOOL adjustPos):
   TListBase(parent, 0)
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
}



//-----------------------------------------------------------------
//   TListBox
TListBox::TListBox(TWinBase *parent, ULONG id, LONG xPos, 
                   LONG yPos, LONG xWidth, LONG yHeight, 
                   BOOL adjustPos, char **items, LONG numItems):
   TListBase(parent, 0)
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

   if (hwndControl != (HWND)NULL)
   {
      for (i=0; i<numItems; i++)
         addItemAt(items[i],i);
   }

}



//-------------------------------------------------------------------
//   ~TlistBox
TListBox::~TListBox()
{

}

//-------------------------------------------------------------------
//   getClassName
const char *TListBox::getClassName()
{
   return "TListBox";
}


//-------------------------------------------------------------------
//   TComboBox
TComboBox::TComboBox(TWinBase *parent, ULONG resource):
   TListBase(parent, resource)
{

}


//-------------------------------------------------------------------
//   TComboBox
TComboBox::TComboBox(TWinBase *parent, ULONG id, LONG xPos, LONG yPos,
                  LONG xWidth, LONG yHeight, BOOL adjustPos):
   TListBase(parent, 0)
{
   ULONG style= WS_VISIBLE | CBS_SIMPLE; 
   if (!adjustPos)
      style |= LS_NOADJUSTPOS;

   register int i;
   fResource = id;
   hwndControl = WinCreateWindow(
                fParent->getHWND(),
                WC_COMBOBOX,
                (PSZ)NULL,
                0, //style,
                xPos, yPos,xWidth, yHeight,
                fParent->getHWND(),
                HWND_TOP,
                fResource,
                NULL, NULL);
}


//-----------------------------------------------------------------
//   TComboBox
TComboBox::TComboBox(TWinBase *parent, ULONG id, LONG xPos, 
                   LONG yPos, LONG xWidth, LONG yHeight, 
                   BOOL adjustPos, char **items, LONG numItems):
   TListBase(parent, 0)
{
   ULONG style= WS_VISIBLE | CBS_SIMPLE;
   if (!adjustPos)
      style |= LS_NOADJUSTPOS;

   register int i;
   fResource = id;
   hwndControl = WinCreateWindow(
                fParent->getHWND(),
                WC_COMBOBOX,
                (PSZ)NULL,
                0, //style,
                xPos, yPos,xWidth, yHeight,
                fParent->getHWND(),
                HWND_TOP,
                fResource,
                NULL, NULL);

   if (hwndControl != (HWND)NULL)
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
//   TPullDownList
TPullDownList::TPullDownList(TWinBase *parent, ULONG resource):
   TListBase(parent, resource)
{

}


//-------------------------------------------------------------------
//   TPullDownList
TPullDownList::TPullDownList(TWinBase *parent, ULONG id, LONG xPos, LONG yPos,
                  LONG xWidth, LONG yHeight, BOOL adjustPos):
   TListBase(parent, 0)
{
   ULONG style= WS_VISIBLE | CBS_DROPDOWNLIST;
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



//-----------------------------------------------------------------
//   TPullDownList
TPullDownList::TPullDownList(TWinBase *parent, ULONG id, LONG xPos, 
                   LONG yPos, LONG xWidth, LONG yHeight, 
                   BOOL adjustPos, char **items, LONG numItems):
   TListBase(parent, 0)
{
   ULONG style= WS_VISIBLE | CBS_DROPDOWNLIST;
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

   if (hwndControl != (HWND)NULL)
   {
      for (i=0; i<numItems; i++)
         addItemAt(items[i],i);
   }

}



//-------------------------------------------------------------------
//   ~TPullDownList
TPullDownList::~TPullDownList()
{

}

//-------------------------------------------------------------------
//   getClassName
const char *TPullDownList::getClassName()
{
   return "TPullDownList";
}


//-------------------------------------------------------------------
//   TPullDown
TPullDown::TPullDown(TWinBase *parent, ULONG resource):
   TListBase(parent, resource)
{

}


//-------------------------------------------------------------------
//   TPullDown
TPullDown::TPullDown(TWinBase *parent, ULONG id, LONG xPos, LONG yPos,
                  LONG xWidth, LONG yHeight, BOOL adjustPos):
   TListBase(parent, 0)
{
   ULONG style= WS_VISIBLE | CBS_DROPDOWN; 
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



//-----------------------------------------------------------------
//   TPullDown
TPullDown::TPullDown(TWinBase *parent, ULONG id, LONG xPos, 
                   LONG yPos, LONG xWidth, LONG yHeight, 
                   BOOL adjustPos, char **items, LONG numItems):
   TListBase(parent, 0)
{
   ULONG style= WS_VISIBLE | CBS_DROPDOWN;
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

   if (hwndControl != (HWND)NULL)
   {
      for (i=0; i<numItems; i++)
         addItemAt(items[i],i);
   }

}



//-------------------------------------------------------------------
//   ~TPullDown
TPullDown::~TPullDown()
{

}

//-------------------------------------------------------------------
//   getClassName
const char *TPullDown::getClassName()
{
   return "TPullDown";
}



