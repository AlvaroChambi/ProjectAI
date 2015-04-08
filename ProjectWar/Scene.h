//
//  Scene.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Scene__
#define __ProjectWar__Scene__

#include <iostream>
#include <list>
#include <vector>
#include "Texture.h"
#include "Event.h"
#include "IGameEventsListener.h"
#include "Map.h"
#include "Sprite.h"
#include "Layout.h"
#include "List.h"

class Scene
{
public:
    Scene();
    Scene(Renderer *renderer);
    virtual ~Scene();
    void attachTexture(Texture* texture);
    void attachSprite(Sprite* sprite);
    void handleEvent(const Event event);
    void registerListener(IGameEventsListener* listener);
    
    void setUIHUD(UIComponent* component);
    void attachMap(Map* map);
    void render();
    //animations
    void update();
private:
    List <Texture*> textureList;
    List <Sprite*> sprites;
    Renderer *renderer;
    IGameEventsListener* eventsListener;
    Map* map;
    Layout* rootLayout;
};

#endif /* defined(__ProjectWar__Scene__) */
