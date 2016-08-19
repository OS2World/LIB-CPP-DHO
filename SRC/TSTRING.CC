/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: tstring.cc 1.2 1995/08/13 03:21:12 teb Exp $ */

#include"tstring.h"
#include"string.h"


TString::TString(char *str)
{
  fString = new char[strlen(str)+1];
  strcpy(fString, str);
}

TString::~TString()
{
   delete fString;
}

     
char *TString::getString()
{
   return fString;
}

TString *TString::Duplicate()
{
   TString *dup;

   dup = new TString(fString);
   return dup;
}

const char *TString::getClassName(void)
{
   return "TString";
}


Boolean TString::isSubString(TString str)
{
   return (Boolean)(strstr(fString, str.fString)!=NULL);
}

TString &TString::operator + (TString &str2)
{
   char *tmp;
   tmp = new char[strlen(fString)+ strlen(str2.fString)+1];
   strcpy(tmp, fString);
   strcat(tmp, str2.fString);

   delete fString;
   fString=tmp;
   return *this;
}


TString &TString::operator = (TString &str2)
{ 
   char *tmp=new char[strlen(str2.fString)+1];

   strcpy(tmp, str2.fString);
   delete fString;
   fString = tmp;

   return *this;
}




Boolean TString::operator ==  (TString &str2)
{
   return (Boolean)(strcmp(fString, str2.fString)==0);
}

Boolean TString::operator < (TString &str2)
{
   return (Boolean)(strcmp(fString, str2.fString)<0);
}

Boolean TString::operator <= (TString &str2)
{
   return (Boolean)(strcmp(fString, str2.fString)<=0);
}

Boolean TString::operator > (TString &str2)
{
   return (Boolean)(strcmp(fString, str2.fString)>0);
}

Boolean TString::operator >= (TString &str2)
{
   return (Boolean)(strcmp(fString, str2.fString)>=0);
}
