/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: notebk.cc 1.5 1995/08/27 08:13:00 teb Exp $ */


#define INCL_DOS
#define INCL_WIN
#include<os2.h>
#include"notebk.h"

#include<stdlib.h>
#include<string.h>



ULONG TNotebook::setStyleULONG()
{
   ULONG tmp = 0;

   if (fNBKattrs.fBindingStyle == spiral)
      tmp = BKS_SPIRALBIND;
   else 
      tmp = BKS_SOLIDBIND;

   return tmp;
}   


//-------------------------------------------------------------------
//  TNotebook
TNotebook::TNotebook(ULONG id, TWinBase *parent):
   TWindow(id, parent)
{
   fId = id;
   fParent = parent;

   fNBKattrs.fBindingStyle = spiral;
   fNBKattrs.fBindingSide = bnd_left;
   fNBKattrs.fTabShape = tabSquare;
   
   fNumPages = fX = fY = fWidth = fHeight = 0;
   fPageIDs = NULL;
}


//-------------------------------------------------------------------
//  TNotebook
TNotebook::TNotebook(ULONG id, TWinBase *parent, binding bnd):
   TWindow(id, parent)
{
   fNBKattrs.fBindingStyle = bnd;
   fNBKattrs.fBindingSide = bnd_left;
   fNBKattrs.fTabShape = tabSquare;
   fNumPages = fX = fY = fWidth = fHeight = 0;
   fPageIDs = NULL;
}



//-------------------------------------------------------------------
//  TNotebook
TNotebook::TNotebook(ULONG id, TWinBase *parent, binding bnd, LONG x, LONG y,
                            LONG width, LONG height):
   TWindow(id, parent)
{
   fNBKattrs.fBindingStyle = bnd;
   fNBKattrs.fBindingSide = bnd_left;
   fNBKattrs.fTabShape = tabSquare;
   fX = x;
   fY = y;
   fHeight = height;
   fWidth = width;
   fNumPages = 0;
   fPageIDs = NULL;
}


//-------------------------------------------------------------------
//  ~TNotebook
TNotebook::~TNotebook()
{
   if (fPageIDs)
      free(fPageIDs);
}


//-------------------------------------------------------------------
//  Init
BOOL TNotebook::init()
{
   ULONG side, shape, bindStyle;

   if (fNBKattrs.fBindingSide == bnd_right)
      side = BKS_BACKPAGESTL;
   else if (fNBKattrs.fBindingSide == bnd_bottom)
      side = BKS_BACKPAGESTR;
   else if (fNBKattrs.fBindingSide == bnd_top)
      side = BKS_BACKPAGESBL;
   else if (fNBKattrs.fBindingSide == bnd_left)
      side = BKS_BACKPAGESBR;

   if (fNBKattrs.fTabShape == tabSquare)
      shape = BKS_SQUARETABS;
   else if (fNBKattrs.fTabShape == tabRound)
      shape = BKS_ROUNDEDTABS;
   else
      shape = BKS_POLYGONTABS;

   if (fNBKattrs.fBindingStyle == spiral)
      bindStyle = BKS_SPIRALBIND | side | shape;
   else
      bindStyle =  BKS_SOLIDBIND | side | shape;


   hwnd = WinCreateWindow(
               fParent->getHWND(),
               WC_NOTEBOOK,
               (PSZ)NULL,
               bindStyle,
               fX, fY, fWidth, fHeight, 
               fParent->getHWND(),
               HWND_BOTTOM,
               fId,
               NULL,
               NULL);

   return ( hwnd!= (HWND)NULL);
}



//-------------------------------------------------------------------
//  insertPageFirst
ULONG TNotebook::insertPageFirst(TWindow *page)
{
   return insertPageFirst(page, NULL, tabNone, NULL);
}

//-------------------------------------------------------------------
//  insertPageFirst
ULONG TNotebook::insertPageFirst(TWindow *page, char *sline)
{
   return insertPageFirst(page, NULL, tabNone, sline);
}


//-------------------------------------------------------------------
//  insertPageFirst
ULONG TNotebook::insertPageFirst(TWindow *page, tabStyle tstyle, char *tabText)
{
   return insertPageFirst(page, NULL, tstyle, tabText);
}


//-------------------------------------------------------------------
//  insertPageFirst
ULONG TNotebook::insertPageFirst(TWindow *page, char *slineText,
                                 tabStyle tstyle, char *tabText)
{
   ULONG style, tab, sline, pageId;
   ULONG *tmpArray;

   style = BKA_AUTOPAGESIZE;

   if (tstyle == tabMajor)
       style |= BKA_MAJOR;
   else if ( tstyle == tabMinor)
       style |= BKA_MINOR;
  
   if (slineText)
       style |= BKA_STATUSTEXTON;

   
   pageId = (ULONG)WinSendMsg(hwnd, BKM_INSERTPAGE,(MPARAM)NULL,
  	               MPFROM2SHORT(style, BKA_FIRST));

   if (page)
      associateWindow(pageId,page);

   if (slineText)
      setStatusLineText(pageId, slineText);

   if (tabText)
      setTabText(pageId, tabText);

   fNumPages++;

   tmpArray = (ULONG*)malloc(sizeof(ULONG)*fNumPages);
   if (tmpArray)
   {
      if (fPageIDs)
         memcpy(&tmpArray[1], fPageIDs, sizeof(ULONG)*(fNumPages-1));
      tmpArray[0] = pageId;
      if (fPageIDs)
         free(fPageIDs);
      fPageIDs = tmpArray;
   }

   return pageId;
}



//-------------------------------------------------------------------
//  insertPageLast
ULONG TNotebook::insertPageLast(TWindow *page)
{
   return insertPageLast(page, NULL, tabNone, NULL);
}



//-------------------------------------------------------------------
//  insertPageLast
ULONG TNotebook::insertPageLast(TWindow *page, char *sline)
{
   return insertPageLast(page, sline, tabNone, NULL);
}


//-------------------------------------------------------------------
// insertPageLast
ULONG TNotebook::insertPageLast(TWindow *page, tabStyle tstyle, char *tabText)
{
   return insertPageLast(page, NULL, tstyle, tabText);
}


//-------------------------------------------------------------------
//  insertPageLast
ULONG TNotebook::insertPageLast(TWindow *page, char *slineText,
                                tabStyle tstyle, char *tabText)
{
   ULONG style, tab, sline, pageId;
   ULONG *tmpArray;

   if (tstyle == tabMajor)
       tab = BKA_MAJOR;
   else if ( tabMinor == tabMinor)
       tab = BKA_MINOR;
   else 
       tab=0;

   if (slineText)
       sline = BKA_STATUSTEXTON;
   else
       sline = 0;

   style = tab | sline | BKA_AUTOPAGESIZE;

   pageId = (ULONG)WinSendMsg(hwnd, BKM_INSERTPAGE,(MPARAM)NULL,
                 MPFROM2SHORT(style, BKA_LAST));

   if (page)
      associateWindow(pageId,page);

   if (slineText)
      setStatusLineText(pageId, slineText);

   if (tabText)
      setTabText(pageId,tabText);

   fNumPages++;
   
   tmpArray = (ULONG*)realloc(fPageIDs, sizeof(ULONG)*fNumPages);
   if (tmpArray)
   {
      fPageIDs = (ULONG*)tmpArray;
      fPageIDs[fNumPages-1] = pageId;
   }

   return pageId;

}


//-------------------------------------------------------------------
//  setStatusLineText
void TNotebook::setStatusLineText(ULONG pageId, char *slineText)
{
   WinSendMsg(hwnd, BKM_SETSTATUSLINETEXT, 
             (MPARAM)pageId, MPFROMP((PSZ)slineText));
}


//-------------------------------------------------------------------
//  setStatusLineText
void TNotebook::setTabText(ULONG pageId, char *slineText)
{
   WinSendMsg(hwnd, BKM_SETTABTEXT,
             (MPARAM)pageId, MPFROMP((PSZ)slineText));
}



//-------------------------------------------------------------------
//  setStatusLineText
void TNotebook::setTabBitmap(ULONG pageId, HBITMAP hbm)
{
   WinSendMsg(hwnd, BKM_SETTABBITMAP, 
             (MPARAM)pageId, MPFROMLONG((ULONG)hbm));
}


//-------------------------------------------------------------------
//  deletePage
void TNotebook::deletePage(ULONG pageid)
{
   BOOL cont;
   LONG i, j;
   ULONG *tmpArray;

   WinSendMsg(hwnd, BKM_DELETEPAGE, 
              MPFROMLONG(pageid), (MPARAM)BKA_SINGLE);
 
   cont = TRUE;
   i = 0;
   while (cont)
   {
      if (fPageIDs[i] == pageid)
      {
         for (j=i; j<fNumPages; j++)
            fPageIDs[j]=fPageIDs[j+1];
            tmpArray = (ULONG*)realloc(fPageIDs, sizeof(ULONG)*(fNumPages-1));
            if (tmpArray)
            {
              fPageIDs = (ULONG*)tmpArray;
            }
      }

      i++;
      if (i==fNumPages)
        cont=FALSE;
   }

   fNumPages--;
}



//-------------------------------------------------------------------
//  deleteFirstPage
void TNotebook::deleteFirstPage()
{
   deletePage(fPageIDs[0]);
}



//-------------------------------------------------------------------
//  deleteLastPage
void TNotebook::deleteLastPage()
{
   deletePage(fPageIDs[fNumPages-1]);
}

//-------------------------------------------------------------------
//
void TNotebook::associateWindow(ULONG pageId, TWindow *win)
{
   WinSendMsg(hwnd, BKM_SETPAGEWINDOWHWND,
              MPFROMLONG(pageId), MPFROMHWND(win->getHWND()));
}


//-------------------------------------------------------------------
void TNotebook::setMajorTabSize(ULONG x, ULONG y)
{
   WinSendMsg(hwnd, BKM_SETDIMENSIONS,
              MPFROM2SHORT(x, y), MPFROMSHORT(BKA_MAJORTAB));

}


//-------------------------------------------------------------------
void TNotebook::setMinorTabSize(ULONG x, ULONG y)
{
   WinSendMsg(hwnd, BKM_SETDIMENSIONS,
              MPFROM2SHORT(x, y), MPFROMSHORT(BKA_MINORTAB));
}

//-------------------------------------------------------------------
//
void TNotebook::associateDlog(ULONG pageId, ULONG dlogRes)
{
   SEL sel = NULL;
   PDLGTEMPLATE pDlgt;
   HWND hwndPage;

/*   DosGetResource(NULL, RT_DIALOG, dlogRes, (DLGTEMPLATE*)&sel);

   handPage = WinCreateDlg(HWND_DESKTOP, hwnd,    
   pDlgt = MAKEP(sel, 0);
   WinSendMsg(hwnd, BKM_SETPAGEWINDOWHWND,
              MPFROMLONG(pageId), MPFROMHWND(hwndPage));
*/
}


