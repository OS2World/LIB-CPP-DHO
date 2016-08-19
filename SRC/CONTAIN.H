/****************************************/
/*    Developer Helper Object Set       */
/*  (C) 1994-95 Thomas E. Bednarz, Jr.  */
/*     All rights reserved              */
/***************************************/

/* $Id: contain.h 1.3 1995/08/13 03:21:12 teb Exp $ */

#ifndef __CONTAINER_H__
#define __CONTAINER_H__

#include<window.h>

/* *************************************************************
    * the class TContainer Window implements a wrapper         *
    * around the Container objects included in Presentation    *
    * manager.  Currently, all types of container views except *
    * tree and detal view are supported.  These will be        *
    * included in future DHO releases...                       *
    *                                                          *
    ************************************************************ */


typedef struct _IconInfo
{
   LONG iconId;
   char *iconName;
} ContainerIconInfo;

typedef ContainerIconInfo *PContainerIconInfo;

enum ContainerViewType {icon, name_flowed, name_nonflowed,
                        text_flowed, text_nonflowed};


class TContainerWindow : public TWinBase
{
      TWinBase *fParent;
      BOOL fReadOnly;
      ULONG fId;
   public:
      TContainerWindow(ULONG id, TWinBase *parent, BOOL readOnly);
      virtual ~TContainerWindow();
      virtual BOOL init();
      void insertItem(HPOINTER icon, PSZ iconName);
      void insertItem(LONG iconId, PSZ iconName);
      void insertItems(PContainerIconInfo items, LONG numItems);
      void setViewType(ContainerViewType viewType);
      void removeItem(USHORT item);
      void removeAll();
};



#endif


