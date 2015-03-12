//
//  Scene.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 10/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Scene.h"

Scene::Scene(Renderer* renderer)
{
    numTextures = 0;
    this->renderer = renderer;
}

Scene::~Scene()
{

}

void Scene::attachTexture(Texture* texture)
{
    textureList[numTextures] = texture;
    numTextures++;
}

void Scene::render()
{
    for(int i = 0; i < numTextures; i++){
        renderer->drawTexture(textureList[i]);
    }
}

void Scene::registerListener(IGameEventsListener *listener)
{
    this->eventsListener = listener;
}

void Scene::handleEvent(const Event event)
{
    switch (event.type) {
        case ON_MOUSE_DOWN_EVENT:
            if(this->eventsListener != nullptr){
                for (int i = 0; i < numTextures; i++) {
                    //TODO if clicked position match with the given texture area notify event
                }
                //TODO if there are no given matches just send scene clicked event
                Point position;
                eventsListener->onSceneClicked(position);
            }
            break;
        default:
            break;
    }
}