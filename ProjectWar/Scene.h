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
#include "Camera.h"

class SceneManager;
class Scene
{
public:
    Scene(Renderer* renderer, SceneManager* manager);
    virtual ~Scene();
    
    virtual void onSceneStarted() = 0;
    virtual void onScenePaused() = 0;
    virtual void onSceneFinished() = 0;
    
    void attachTexture(Texture* texture);
    void attachSprite(Sprite* sprite);
    void handleEvent(const Event event);
    void registerListener(IGameEventsListener* listener);
    
    int getExtras();
    void setExtras(int extras);
    
    void registerCamera(Camera* camera);
    Camera* getCamera();
    
    void registerPopUp(Layout* popUp);
    void showPopup();
    void hidePopUp();
    
    void setUIHUD(UIComponent* component);
    void attachMap(Map* map);
    void render();
    //animations
    void update();
private:
    int extras;
    std::list <Texture*> textureList;
    std::list <Sprite*> sprites;
    Renderer *renderer;
    IGameEventsListener* eventsListener;
    SceneManager* manager;
    Map* map;
    Layout* rootLayout;
    //TODO not sure if we are gonna need this here...
    Camera* camera;
    Layout* popUp;
};

#endif /* defined(__ProjectWar__Scene__) */
