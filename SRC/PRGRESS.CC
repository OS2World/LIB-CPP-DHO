/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: prgress.cc 1.4 1995/08/26 22:51:59 teb Exp $ */


#include<prgress.h>


//---------------------------------------------------
//   TProgressBar
TProgressBar::TProgressBar(ULONG id, TWinBase *parent, 
                          ULONG x, ULONG y, ULONG cx, ULONG cy):
   TWindow(id, parent)
{
   this->x = x;
   this->y = y;
   this->cx = cx;
   this->cy = cy;
   perDone = 0;
   bg = CLR_DARKGRAY;
   fg = CLR_BLUE;
   brdr = CLR_WHITE;
}


//---------------------------------------------------
//  ~TProgressBar
TProgressBar::~TProgressBar()
{

}
      


//---------------------------------------------------
//  init
BOOL TProgressBar::init()
{
   if (TWindow::init())
   {
      setWindowPosition(x,y);
      setWindowSize(cx, cy);
      enableUpdate(TRUE);
   }
   return FALSE;
}



//---------------------------------------------------
//  paintWindow
void TProgressBar::paintWindow(HPS ps, RECTL rcl)
{
   RECTL rctl, area;
   float diff;
   area = rcl;

   WinFillRect(ps, &area, bg);
   WinDrawBorder(ps, &rcl, 2, 2, brdr, fg, 0);

   area.xLeft+=5;
   area.xRight-=5;
   area.yTop-=5;
   area.yBottom+=5;

   diff = area.xRight - area.xLeft;
   diff = (diff * (perDone*.01));
   area.xRight = area.xLeft + diff;


   WinFillRect(ps, &area, fg);
}
 
 
//---------------------------------------------------
//    setPercentDone
void TProgressBar::setPercentDone(LONG percent)
{
   perDone = percent;
   forceUpdate();
}


//---------------------------------------------------
//   getPercentDone
ULONG TProgressBar::getPercentDone()
{
   return perDone;
}


//---------------------------------------------------
//   setBackground
void TProgressBar::setBackground(ULONG clr_index)
{
  bg = clr_index;
}


//---------------------------------------------------
//   setForeground
void TProgressBar::setForeground(ULONG clr_index)
{
   fg = clr_index;
}


//---------------------------------------------------
//   setBorder
void TProgressBar::setBorder(ULONG clr_index)
{
   brdr = clr_index;
}

