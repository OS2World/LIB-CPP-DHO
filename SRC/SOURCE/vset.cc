/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: vset.cc 1.8 1995/08/26 23:55:07 teb Exp $ */


#include"vset.h"
#include<os2.h>


//-------------------------------------------------------------------
//  TValueSet
TValueSet::TValueSet(ULONG id, TWinBase *parent, USHORT rows, USHORT cols):
    TWinBase(id)
{
   fRows = rows;
   fCols = cols;
   fParent = parent;
   fId = id;
 
   vscData.cbSize = sizeof(VSCDATA);
   vscData.usRowCount = fRows;
   vscData.usColumnCount = fCols;
   ulVSetStyle= 0;

//  set default values
   fVSetAttr.items = bitmaps;
   fVSetAttr.itemBorder = TRUE;
   fVSetAttr.setBorder = TRUE;
   fVSetAttr.scaleItems = FALSE;
   fVSetAttr.x= 0;
   fVSetAttr.y = 0;
   fVSetAttr.width = 0;
   fVSetAttr.height = 0;

}


//-------------------------------------------------------------------
//  ~TValueSet
TValueSet::~TValueSet()
{

}


//-------------------------------------------------------------------
//  getNumRows
USHORT TValueSet::getNumRows()
{
   return fRows;
}


//-------------------------------------------------------------------
//  getNumCols
USHORT TValueSet::getNumCols()
{
   return fCols;
}


//-------------------------------------------------------------------
//  getClassName
const char *TValueSet::getClassName(void)
{
   return "TValueSet";
}


//-------------------------------------------------------------------
//  MakeFrame
BOOL TValueSet::init()
{

   switch (fVSetAttr.items)
   {
      case colors:
         ulVSetStyle |= VS_RGB;
         break;
      case bitmaps:
         ulVSetStyle |= VS_BITMAP;
         break;
      case icon:
         ulVSetStyle |= VS_ICON;
         break;
      case text:
         ulVSetStyle |= VS_TEXT;
     break;
   }
   
   if (fVSetAttr.itemBorder)
      ulVSetStyle |= VS_ITEMBORDER;
   if (fVSetAttr.setBorder)
      ulVSetStyle |= VS_BORDER;
   if ((fVSetAttr.items == bitmaps) && (fVSetAttr.scaleItems))
      ulVSetStyle |= VS_SCALEBITMAPS ;

   fX = fVSetAttr.x;
   fY = fVSetAttr.y;
   fcX = fVSetAttr.width;
   fcY = fVSetAttr.height;

   if (fId == FID_CLIENT)
      ulVSetStyle |= FCF_SHELLPOSITION;   

      hwnd = WinCreateWindow(fParent->getHWND(),
                         WC_VALUESET, NULL, ulVSetStyle,
                         fX,fY,fcX,fcY, fParent->getHWND(), HWND_TOP,
                         fId, &vscData, NULL);

    return (hwnd != NULL);
}



//-------------------------------------------------------------------
//  setItem
void TValueSet::setItem(USHORT row, USHORT col, VOID *item)
{
   WinSendMsg(hwnd, VM_SETITEM,MPFROM2SHORT(row, col),
			  MPFROMLONG(item));
}


//-------------------------------------------------------------------
//  DoControl
MRESULT TValueSet::DoControl(MPARAM mParam1)
{
   if (SHORT2FROMMP(mParam1) == VN_SELECT) 
   {
      ULONG ulRowCol;
      CHAR szBuffer[20];
	  ulRowCol = (ULONG) WinSendMsg(hwnd,
  			      VM_QUERYSELECTEDITEM,NULL,NULL);

      fData = ulRowCol;
	  return (MRESULT)TRUE;
   }
   return (MRESULT)FALSE;
}

//-------------------------------------------------------------------
//  getSelection
void TValueSet::getSelection(SHORT &row, SHORT &col)
{
   row = SHORT1FROMMP(fData);
   col = SHORT2FROMMP(fData);   
}
	
