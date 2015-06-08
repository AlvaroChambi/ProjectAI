//
//  Scene.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Scene.h"

Scene::Scene()
{

}

Scene::Scene(Renderer* renderer) :textureList(), sprites()
{
    this->renderer = renderer;
    this->map = nullptr;
    //Create a virtual layout parent just to hold the screen dimensions
    rootLayout = new Layout;
}

Scene::~Scene()
{
    
}

void Scene::setExtras(int extras)
{
    this->extras = extras;
}

int Scene::getExtras()
{
    return extras;
}

void Scene::attachTexture(Texture* texture)
{
    
    textureList.push_back(texture);

}

void Scene::attachSprite(Sprite *sprite)
{
    sprites.push_back(sprite);
}

void Scene::attachMap(Map *map)
{
    this->map = map;
}

void Scene::setUIHUD(UIComponent *component)
{
    //Fixed windows dimensions, change it...
    rootLayout->setWidth(640);
    rootLayout->setHeight(480);
    
    rootLayout->addComponent(component);
}

void Scene::render()
{
    if( map != nullptr ){
        map->drawMap(renderer);
    }
    
    for(Texture* texture : textureList){
        if(texture->isVisible()){
            renderer->drawTexture(texture);
        }
    }
    //Sprites in this case are mvc oriented 
    for(Sprite* sprite : sprites){
        sprite->render(renderer);
    }
    
    //InfoMap
    //TODO hiding info map
    if(map != nullptr){
        map->drawInfoMap(renderer);
    }
    
    rootLayout->render(renderer);
}

//Sprites animations ticks
void Scene::update()
{
    for (Sprite* sprite : sprites) {
        sprite->updateFrame();
    }
}

void Scene::registerListener(IGameEventsListener *listener)
{
    this->eventsListener = listener;
}

void Scene::handleEvent(const Event event)
{
    //TODO Do not trigger event if the texture is not visible
    bool eventHandled = false;
    Point position = Point(event.x, event.y);
    switch (event.type) {
        case ON_MOUSE_DOWN_EVENT:
            if(this->eventsListener != nullptr){
                for (Texture* texture : textureList) {
                    //if clicked position match with the given texture area notify event
                    if(texture->matchPosition(position) && texture->isVisible()){
                        eventsListener->onTextureClicked(*texture);
                        eventHandled = true;
                    }
                }
                for(Sprite* sprite : sprites){
                    //if clicked position match with the given sprite size notify event
                    if(sprite->matchPosition(position) && sprite->getTexture()->isVisible()){
                        eventsListener->onSpriteClicked(sprite->getID());
                        eventHandled = true;
                    }

                }
                
                UIComponent* component = rootLayout->matchEvent(position);
                if(component != nullptr){
                    eventsListener->onUIComponentClicked(*component);
                }
                
                if(!eventHandled){
                    Tile* tile = nullptr;
                    // if there are no previous matches just send scene clicked event
                    if (map != nullptr) {
                        tile = map->matchEvent(position);
                    }
                    
                    if(tile != nullptr){
                        eventsListener->onMapClicked(*tile);
                    }
                }
                
                eventsListener->onSceneClicked(position);
            }
            break;
        default:
            break;
    }
}