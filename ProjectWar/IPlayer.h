//
//  IPlayer.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 30/5/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef IPlayer_h
#define IPlayer_h

class IPlayer {
public:
    virtual bool hasUnitAlive() = 0;
    virtual bool hasCapturedHQ( Player* enemy ) = 0;
};

#endif /* IPlayer_h */
