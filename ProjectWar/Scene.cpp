//
//  Scene.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Scene.h"

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

void Scene::attachTexture(Texture* texture)
{
    
    textureList.add(texture);

}

void Scene::attachSprite(Sprite *sprite)
{
    sprites.add(sprite);
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
    
    for(int i = 0; i < textureList.getSize(); i++){
        if(textureList.getElement(i)->isVisible()){
            renderer->drawTexture(textureList.getElement(i));
        }
    }
    //Sprites in this case are mvc oriented 
    for(int i = 0; i < sprites.getSize(); i++){
        sprites.getElement(i)->render(renderer);
       /*Sprite* sprite =sprites.getElement(i);
        if (sprite->getTexture()->isVisible()) {
            renderer->drawTexture(sprite->getTexture(), sprite->getWidth(), sprite->getHeight());
        }*/
    }
    
    //InfoMap
    map->drawInfoMap(renderer);
    
    rootLayout->render(renderer);
}

//Sprites animations ticks
void Scene::update()
{
    for (int i = 0; i < sprites.getSize(); i++) {
        sprites.getElement(i)->updateFrame();
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
                for (int i = 0; i < textureList.getSize(); i++) {
                    //if clicked position match with the given texture area notify event
                    if(textureList.getElement(i)->matchPosition(position) && textureList.getElement(i)->isVisible()){
                        eventsListener->onTextureClicked(*textureList.getElement(i));
                        eventHandled = true;
                    }
                }
                for(int i = 0; i < sprites.getSize(); i++){
                    //if clicked position match with the given sprite size notify event
                    if(sprites.getElement(i)->matchPosition(position) && sprites.getElement(i)->getTexture()->isVisible()){
                        eventsListener->onSpriteClicked(sprites.getElement(i)->getID());
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