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
    camera = new Camera();
    //Create a virtual layout parent just to hold the screen dimensions
    rootLayout = new Layout;
    popUp = new Layout;
}

Scene::~Scene()
{
    
}

void Scene::registerCamera(Camera *camera)
{
    this->camera = camera;
    renderer->registerCamera(camera);
}

Camera* Scene::getCamera()
{
    return camera;
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

void Scene::registerPopUp(Layout *popUp)
{
    this->popUp->setWidth(640);
    this->popUp->setHeight(480);
    
    this->popUp->setHUD(true);
    this->popUp->addComponent(popUp);
    this->popUp->setVisible(false);
}

void Scene::showPopup()
{
    popUp->setVisible(true);
}

void Scene::hidePopUp()
{
    popUp->setVisible(false);
}

void Scene::setUIHUD(UIComponent *component)
{
    //TODO Fixed windows dimensions, change it...
    rootLayout->setWidth(640);
    rootLayout->setHeight(480);
    
    //everything here is rendered without any offset
    //hud flag must be update before adding any component
    rootLayout->setHUD(true);
    rootLayout->addComponent(component);
}

void Scene::render()
{
    //TODO maybe send the offset to the renderer instead of the camera itself
    if( map != nullptr ){
        map->drawMap(renderer, camera);
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
    
    popUp->render(renderer);
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

//TODO handle events in a higher level
void Scene::handleEvent(const Event event)
{
    //TODO Do not trigger event if the texture is not visible
    bool eventHandled = false;
    //Position of the event adding the camera offset
    Point position = Point(event.x , event.y) + camera->position;
    switch (event.type) {
        case ON_MOUSE_DRAG:
        {
            Point newPosition = camera->position - Point(event.xRelative, event.yRelative);
            camera->position = newPosition;
        }
            break;
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
                
                //Avoiding camera offset in HUD elements
                UIComponent* component = rootLayout->matchEvent(Point(event.x, event.y));
                if(component != nullptr){
                    eventsListener->onUIComponentClicked(*component);
                }
                //TODO maybe check if the event hasnt been handled yet
                component = popUp->matchEvent(Point(event.x, event.y));
                if (component != nullptr) {
                    eventsListener->onUIComponentClicked(*component);
                }
                
                if(!eventHandled){
                    Tile* tile = nullptr;
                    int id = -1;
                    // if there are no previous matches just send scene clicked event
                    if (map != nullptr) {
                        tile = map->matchEvent(position);
                    }
                    
                    if (map != nullptr){
                        id = map->matchSpriteEvent(position);
                    }
                    
                    if(tile != nullptr){
                        eventsListener->onMapClicked(*tile);
                    }
                    
                    if (id != -1) {
                        eventsListener->onSpriteClicked(id);
                    }
                }
                
                eventsListener->onSceneClicked(position);
            }
            break;
        default:
            break;
    }
}