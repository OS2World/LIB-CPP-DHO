/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: conttest.h 1.1 1995/08/15 01:59:53 teb Exp $ */

#define ID_POPUPMENU 100

#define IDM_ICONVIEW 200
#define IDM_NAME 201
#define IDM_TEXT 202
#define IDM_DELETE 203
#define IDM_NAME_FLOWED 204
#define IDM_NAME_NONFLOWED 205
#define IDM_TEXT_FLOWED 206
#define IDM_TEXT_NONFLOWED 207
#define IDM_ADDITEMS 208
#define IDM_DELETE1 209
#define IDM_DELETE2 210
#define IDM_DELETE3 211
#define IDM_DELETEALL 212
#define IDM_PRODINFO 213
#define IDM_QUIT 214
#define IDM_SEP 215

#define NUM_SYS_ICONS 19


typedef struct _sysIconInfo
{
   LONG iconId;
   char* iconName;
} IconInfo;


