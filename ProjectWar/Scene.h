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
#include "Renderer.h"
#include "Event.h"
#include "IGameEventsListener.h"
#include "Map.h"

class Scene
{
public:
    Scene();
    Scene(Renderer *renderer);
    virtual ~Scene();
    void attachTexture(Texture* texture);
    void handleEvent(const Event event);
    void registerListener(IGameEventsListener* listener);
    void attachMap(Map* map);
    void render();
private:
    //TODO Change it for a linked list or a map
    Texture* textureList[10];
    std::vector<Texture*> textureVector;
    int numTextures;
    Renderer *renderer;
    IGameEventsListener* eventsListener;
    Map* map;
};

#endif /* defined(__ProjectWar__Scene__) */
