//
//  UnitUIView.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 4/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__UnitUIView__
#define __ProjectWar__UnitUIView__

#include <stdio.h>
#include "HorizontalLayout.h"
#include "Unit.h"

class UnitUIView : public Observer, public HorizontalLayout
{
public:
    UnitUIView();
    UnitUIView(int id);
    virtual ~UnitUIView();
    void update(Update update);
    void setModel(Model* model);
private:
    void updateComponents();
    Unit* unit;
};

#endif /* defined(__ProjectWar__UnitUIView__) */
