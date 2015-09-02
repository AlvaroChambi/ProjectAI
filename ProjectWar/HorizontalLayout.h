//
//  HorizontalLayout.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 12/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__HorizontalLayout__
#define __ProjectWar__HorizontalLayout__

#include <stdio.h>
#include "Layout.h"

class HorizontalLayout : public Layout
{
public:
    HorizontalLayout(int id);
    HorizontalLayout();
    ~HorizontalLayout();
    
    void measureDisposition();
};

#endif /* defined(__ProjectWar__HorizontalLayout__) */
