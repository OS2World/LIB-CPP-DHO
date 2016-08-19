/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: notebk.h 1.3 1995/08/13 03:21:12 teb Exp $ */


#ifndef __NOTEBK_H__
#define __NOTEBK_H__

#include<window.h>

enum binding {solid, spiral};
enum tabStyle {tabMajor, tabMinor, tabNone};
enum tabShape {tabSquare, tabRound, tabPoly};
enum tabAlign {tabLeft, tabRight, tabCenter};
enum bindSide {bnd_top, bnd_bottom, bnd_left, bnd_right};

struct NotebookAttrs
{
   binding fBindingStyle;
   bindSide fBindingSide;
   tabShape fTabShape;   
};

class TNotebook: public TWindow
{
   protected:
      int fNumPages;
      ULONG *fPageIDs;
      LONG fX, fY, fWidth, fHeight;
      ULONG fId;
      TWinBase *fParent;

      ULONG setStyleULONG();

   public:
      NotebookAttrs fNBKattrs;             

      TNotebook(ULONG id, TWinBase *parent);
      TNotebook(ULONG id, TWinBase *parent, binding bnd);
      TNotebook( ULONG id, TWinBase *parent, binding bnd, LONG x, LONG y,
                            LONG width, LONG height);
      ~TNotebook();
      virtual BOOL init();

      ULONG insertPageFirst(TWindow *page);
      ULONG insertPageFirst(TWindow *page, char *sline);
      ULONG insertPageFirst(TWindow *page, tabStyle tstyle, char *tabText);
      ULONG insertPageFirst(TWindow *page, char *slineText,
                            tabStyle tstyle, char *tabText);

      ULONG insertPageLast(TWindow *page);
      ULONG insertPageLast(TWindow *page, char *sline);
      ULONG insertPageLast(TWindow *page, tabStyle tstyle, char *tabText);
      ULONG insertPageLast(TWindow *page, char *slineText,
                           tabStyle tstyle, char *tabText);

      void deletePage(ULONG pageid);
      void deleteFirstPage();
      void deleteLastPage();
      void setStatusLineText(ULONG pageId, char *slineText);
      void setTabText(ULONG pageId, char *tabText);
      void setTabBitmap(ULONG pageId, HBITMAP hbm);
      void associateWindow(ULONG pageId, TWindow *win);
      void associateDlog(ULONG pageId, ULONG dlogRes);
      void setMajorTabSize(ULONG x, ULONG y);
      void setMinorTabSize(ULONG x, ULONG y);
      
};
#endif

