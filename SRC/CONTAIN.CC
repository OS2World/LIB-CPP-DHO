/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: contain.cc 1.3 1995/08/13 03:21:12 teb Exp teb $ */



#include"contain.h"

//----------------------------------------------------------
//  TContainerWindow
TContainerWindow::TContainerWindow(ULONG id, TWinBase *parent, BOOL readOnly):
   TWinBase(id)
{   
   fId = id;
   fParent = parent;
   fReadOnly = readOnly;
}


//----------------------------------------------------------
//  ~TContainerWindow
TContainerWindow::~TContainerWindow()
{

}


//----------------------------------------------------------
//  Init
BOOL TContainerWindow::init()
{

   ULONG style = CCS_AUTOPOSITION;
   if (fReadOnly)
      style |= CCS_READONLY;

   hwnd = WinCreateWindow(
                fParent->getHWND(),
                WC_CONTAINER,
                NULL,
                style,
                0,0,0,0,
                fParent->getHWND(),
                HWND_BOTTOM,
                fId,
                NULL, NULL);

   return (hwnd != (HWND)NULL);
}


//----------------------------------------------------------
//  insertItem
void TContainerWindow::insertItem(HPOINTER icon, PSZ iconName)
{
   PRECORDCORE pRecordCore;
   RECORDINSERT recordInsert;

    pRecordCore = (PRECORDCORE) WinSendMsg(hwnd, CM_ALLOCRECORD,
                 0, MPFROMLONG(1));
 
    pRecordCore->cb = sizeof(RECORDCORE);

    pRecordCore->hptrIcon = icon;

    pRecordCore->pszIcon = pRecordCore->pszName =
           pRecordCore->pszText = iconName;

   recordInsert.cb = sizeof(RECORDINSERT);
   recordInsert.pRecordParent = NULL;
   recordInsert.pRecordOrder = (PRECORDCORE)CMA_END;
   recordInsert.zOrder = (USHORT)CMA_TOP;
   recordInsert.cRecordsInsert = 1;
   recordInsert.fInvalidateRecord = TRUE;

   WinSendMsg(hwnd, CM_INSERTRECORD,
                 (PRECORDCORE)pRecordCore, &recordInsert);

}


//----------------------------------------------------------
//  insertItem
void TContainerWindow::insertItem(LONG iconId, PSZ iconName)
{
   HPOINTER icon;
 
   icon = WinQuerySysPointer(HWND_DESKTOP, iconId,FALSE);
   insertItem(icon, iconName);
}


//----------------------------------------------------------
//  insertItems
void TContainerWindow::insertItems(PContainerIconInfo items, LONG numItems)
{
   PRECORDCORE pRecordCore, pStartingRecordCore;
   RECORDINSERT recordInsert;
   LONG i;

    pRecordCore = (PRECORDCORE) WinSendMsg(hwnd, CM_ALLOCRECORD,
                 0, MPFROMLONG(numItems));
 
    pStartingRecordCore = pRecordCore;

   for (i=0; i<numItems; i++)
   {
       pRecordCore->cb = sizeof(RECORDCORE);
       pRecordCore->hptrIcon = WinQuerySysPointer(HWND_DESKTOP, items[i].iconId, FALSE);

       pRecordCore->pszIcon = pRecordCore->pszName =
              pRecordCore->pszText = (PSZ)items[i].iconName;

      pRecordCore = pRecordCore->preccNextRecord;
   }

   recordInsert.cb = sizeof(RECORDINSERT);
   recordInsert.pRecordParent = NULL;
   recordInsert.pRecordOrder = (PRECORDCORE)CMA_END;
   recordInsert.zOrder = (USHORT)CMA_TOP;
   recordInsert.cRecordsInsert = numItems;
   recordInsert.fInvalidateRecord = TRUE;

   WinSendMsg(hwnd, CM_INSERTRECORD,
                 (PRECORDCORE)pStartingRecordCore, &recordInsert);
}


//----------------------------------------------------------
//  setViewType
void TContainerWindow::setViewType(ContainerViewType viewType)
{
   CNRINFO cnrinfo;
   if ( viewType == icon )
       cnrinfo.flWindowAttr = CV_ICON;
   else if ( viewType == name_flowed )
       cnrinfo.flWindowAttr = CV_NAME | CV_FLOW;
   else if ( viewType == name_nonflowed )
       cnrinfo.flWindowAttr = CV_NAME;
   else if ( viewType == text_flowed )
       cnrinfo.flWindowAttr = CV_TEXT | CV_FLOW;
   else if ( viewType == text_nonflowed )
       cnrinfo.flWindowAttr = CV_TEXT;

   WinSendMsg(hwnd, CM_SETCNRINFO,
                  &cnrinfo, MPFROMLONG( CMA_FLWINDOWATTR));
}

//----------------------------------------------------------
//  removeItem
void TContainerWindow::removeItem(USHORT item)
{
   USHORT removeStyle = CMA_INVALIDATE | CMA_FREE;
   PRECORDCORE start;
   start = (PRECORDCORE)WinSendMsg(hwnd, CM_QUERYRECORD,
                 NULL, MPFROM2SHORT(CMA_FIRST, CMA_ITEMORDER));


   WinSendMsg(hwnd, CM_REMOVERECORD, 
                 start, MPFROM2SHORT(1, removeStyle));
}

//----------------------------------------------------------
//  removeAll
void TContainerWindow::removeAll()
{
   USHORT removeStyle = CMA_INVALIDATE | CMA_FREE;

   WinSendMsg(hwnd, CM_REMOVERECORD, 
                 NULL, MPFROM2SHORT(0, removeStyle));
}	

