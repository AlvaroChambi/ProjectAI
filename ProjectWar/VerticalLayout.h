//
//  VerticalLayout.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 8/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__VerticalLayout__
#define __ProjectWar__VerticalLayout__

#include <stdio.h>
#include "Layout.h"

class VerticalLayout : public Layout
{
public:
    
    VerticalLayout();
    virtual ~VerticalLayout();
    
    void updatePosition(UIComponent* component);

};

#endif /* defined(__ProjectWar__VerticalLayout__) */
