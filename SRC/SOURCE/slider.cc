/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: slider.cc 1.4 1995/08/13 03:21:12 teb Exp $ */


#include"slider.h"
#include"winbase.h"
#include"object.h"
#define INCL_WIN
#define INCL_WINSTDSLIDER
#include<os2.h>


//-------------------------------------------------------------------
//   TSlider
TSlider::TSlider(TWinBase *parent, ULONG resource):
    TControl(parent, resource)
{

}


//-------------------------------------------------------------------
//   TSlider
TSlider::TSlider(TWinBase *parent, Direction dir, SHORT x, SHORT y, SHORT width, SHORT height):
     TControl(parent)
{
   ULONG sliderStyle;
   SLDCDATA sldcData;

   sldcData.cbSize = sizeof(SLDCDATA);
   sldcData.usScale1Increments = 6;
   sldcData.usScale1Spacing = 0;

   sliderStyle = SLS_PRIMARYSCALE1 | SLS_BUTTONSRIGHT;

   if (dir == horizontal)
      sliderStyle |= SLS_HORIZONTAL;
   else
      sliderStyle |= SLS_VERTICAL;

   hwndControl = WinCreateWindow(
                     fParent->getHWND(),
                     WC_SLIDER,
                     (PSZ)NULL,
                     sliderStyle,
                     x,y,width, height,
                     fParent->getHWND(),
                     HWND_TOP,
                     100,
                     &sldcData,
                     (PVOID)NULL);

}


//-------------------------------------------------------------------
//   ~TSlider
TSlider::~TSlider()
{

}


//-------------------------------------------------------------------
//   placeAtTick
void TSlider::placeAtTick(SHORT no)
{
   SendMessage(SLM_SETSLIDERINFO,
                 MPFROM2SHORT(SMA_SLIDERARMPOSITION,
                                    SMA_INCREMENTVALUE),
                 (MPARAM)no);
}


//-------------------------------------------------------------------
//   tickSize
void TSlider::tickSize(SHORT pix)
{
   SendMessage(SLM_SETTICKSIZE,
                 MPFROM2SHORT(SMA_SETALLTICKS,
                                    pix),
                 (MPARAM)NULL);

}


//-------------------------------------------------------------------
//   setTickText
void TSlider::setTickText(SHORT tick, CHAR *text)
{
   SendMessage(SLM_SETSCALETEXT,
                 MPFROMSHORT(tick),
                 MPFROMP(text));

}


//-------------------------------------------------------------------
//   DetentShaftCenter
void TSlider::DetentShaftCenter(void)
{
   MRESULT armpos = SendMessage((ULONG)SLM_QUERYSLIDERINFO,(MPARAM)MPFROM2SHORT((USHORT)SMA_SLIDERARMPOSITION,
                 (USHORT)SMA_RANGEVALUE), NULL);

    SendMessage(SLM_ADDDETENT,armpos, NULL);
}



//-------------------------------------------------------------------
//   getSliderPos
ULONG TSlider::getSliderPos()
{
   ULONG armpos = (ULONG)SendMessage(SLM_QUERYSLIDERINFO,
                                MPFROM2SHORT(SMA_SLIDERARMPOSITION,SMA_INCREMENTVALUE),
                                (MPARAM)NULL);
   return armpos;
}


//-------------------------------------------------------------------
//   getClassName
const char *TSlider::getClassName()
{
   return "TSlider";
}
