/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: spinbtn.cc 1.2 1995/08/13 03:21:12 teb Exp $ */


#include"spinbtn.h"


//-------------------------------------------------------------------
//   TSpinButton
//       resource control  constructor
TSpinButton::TSpinButton(TWinBase *parent, ULONG resource, LONG min, LONG max):
   TControl(parent, resource)
{
   setLimits(min, max);
}

//-------------------------------------------------------------------
//   TSpinButton
//        client window constructor
TSpinButton::TSpinButton(TWinBase *parent, SpinBtnAttr *etr, LONG xPos, LONG yPos,
                  LONG xWidth, LONG yHeight, LONG min, LONG max):
   TControl(parent)
{
   ULONG SpinStyle = SPBS_MASTER;


   if (etr->lcr == left)
      SpinStyle |= SPBS_JUSTLEFT;
   else if (etr->lcr == right)
      SpinStyle |= SPBS_JUSTLEFT;
   else if (etr->lcr == center)
      SpinStyle |= SPBS_JUSTCENTER;

   if (etr->numberic)
      SpinStyle |= SPBS_NUMERICONLY;
   else
      SpinStyle |= SPBS_ALLCHARACTERS;
   if (etr->fastspin)
      SpinStyle |= SPBS_FASTSPIN;
   if (etr->noBorder)
      SpinStyle |= SPBS_NOBORDER;
   if (etr->readOnly)
      SpinStyle |= SPBS_READONLY;
   if (etr->padZeros)
      SpinStyle |= SPBS_PADWITHZEROS;

   hwndControl = WinCreateWindow(
                      fParent->getHWND(),
                      WC_SPINBUTTON,
                      (PSZ)NULL,
                      SpinStyle,
                      xPos, yPos, xWidth, yHeight,
                      fParent->getHWND(),
                      HWND_TOP,
                      100, (PVOID)NULL, (PVOID)NULL);
   setLimits(min, max);
}


//-------------------------------------------------------------------
//   ~TSpinButton
TSpinButton::~TSpinButton()
{

}


//-------------------------------------------------------------------
//   getClassName
const char *TSpinButton::getClassName()
{
   return "TSpinButton";
}


//-------------------------------------------------------------------
//   setCurrentValue
void TSpinButton::setCurrentValue(LONG cVal)
{
    SendMessage(SPBM_SETCURRENTVALUE, (MPARAM)cVal, (MPARAM)NULL);
}


//-------------------------------------------------------------------
//   getCurrentValue
LONG TSpinButton::getCurrentValue()
{
   return (LONG)SendMessage(SPBM_QUERYVALUE, NULL, NULL);
}


//-------------------------------------------------------------------
//   setLimits
void TSpinButton::setLimits(LONG min, LONG max)
{
   fMin = min;
   fMax = max;

   SendMessage(SPBM_SETLIMITS, (MPARAM)fMax, (MPARAM) fMin);

}

