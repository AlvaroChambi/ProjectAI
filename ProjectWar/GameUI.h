
//
//  GameUI.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__GameUI__
#define __ProjectWar__GameUI__

#include <stdio.h>
#include "Layout.h"
#include "Text.h"

class GameUI : public Layout
{
public:
    GameUI();
    virtual ~GameUI();
    
    void setPlayerName(std::string playerName);
    void setPlayerFounds(int playerFounds);
    void setDay(int day);
    
private:
    Text* playerName;
    Text* playerFounds;
    Text* day;
};

#endif /* defined(__ProjectWar__GameUI__) */
