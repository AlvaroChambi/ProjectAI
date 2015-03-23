//
//  Scene.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Scene.h"

Scene::Scene(Renderer* renderer) : numTextures(0), numSprites(0)
{
    this->renderer = renderer;
    this->map = nullptr;
}

Scene::~Scene()
{
    
}

void Scene::attachTexture(Texture* texture)
{
    
    textureList[numTextures] = texture;
    numTextures++;
}

void Scene::attachSprite(Sprite *sprite)
{
    sprites[numSprites] = sprite;
    numSprites++;
}

void Scene::attachMap(Map *map)
{
    this->map = map;
}

void Scene::render()
{
    if( map != nullptr ){
        map->drawMap(renderer);
    }
    
    for(int i = 0; i < numTextures; i++){
        if(textureList[i]->isVisible()){
            renderer->drawTexture(textureList[i]);
        }
    }
    //Sprites in this case are mvc oriented 
    for(int i = 0; i < numSprites; i++){
        if (sprites[i]->getTexture()->isVisible()) {
            renderer->drawTexture(sprites[i]->getTexture(), sprites[i]->getWidth(), sprites[i]->getHeight());
        }
    }
}

//Sprites animations ticks
void Scene::update()
{
    for (int i = 0; i < numSprites; i++) {
        sprites[i]->updateFrame();
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
                for (int i = 0; i < numTextures; i++) {
                    //if clicked position match with the given texture area notify event
                    if(textureList[i]->matchPosition(position)){
                        eventsListener->onTextureClicked(*textureList[i]);
                        eventHandled = true;
                    }
                }
                for(int i = 0; i < numSprites; i++){
                    //if clicked position match with the given sprite size notify event
                    if(sprites[i]->matchPosition(position)){
                        eventsListener->onSpriteClicked(sprites[i]->getID());
                        eventHandled = true;
                    }

                }
                
                if(!eventHandled){
                    Tile* tile = nullptr;
                    // if there are no given matches just send scene clicked event
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