//
//  MapSelectScene.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 14/8/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include <list>
#include "MapSelectScene.h"
#include "VerticalLayout.h"
#include "HorizontalLayout.h"
#include "Button.h"
#include "Text.h"
#include "TextList.h"

MapSelectScene::MapSelectScene(Renderer* renderer, SceneManager* sceneManager) : Scene(renderer, sceneManager)
{

}

MapSelectScene::~MapSelectScene()
{

}

void MapSelectScene::onSceneStarted()
{
    HorizontalLayout* rootLayout = new HorizontalLayout;
    VerticalLayout* mapSelectLayout = new VerticalLayout;
    VerticalLayout* previewLayout = new VerticalLayout;
    VerticalLayout* titleLayout = new VerticalLayout;
    
    rootLayout->setParams(Params(FILL, FILL, CENTER));
    mapSelectLayout->setParams(Params(300, FILL, CENTER));
    previewLayout->setParams(Params(300, FILL, CENTER));
    //titleLayout->setParams(Params(FILL, 180, CENTER));
    
    Text* mapsTitle = new Text();
    mapsTitle->setParams(Params(100, 50, CENTER));
    mapsTitle->setTextResource("MAPS");
    TextList* mapsList = new TextList;
    
    std::list<std::string> maps;
    maps.push_back("MAP0");
    maps.push_back("MAP1");
    maps.push_back("MAP2");
    
    this->setUIHUD(rootLayout);
    
    rootLayout->addComponent(mapSelectLayout);
    rootLayout->addComponent(previewLayout);
    
    mapSelectLayout->addComponent(titleLayout);
    mapSelectLayout->addComponent(mapsList);
    
    //titleLayout->addComponent(mapsTitle);
    
    mapsList->setList(maps);
    
}

void MapSelectScene::onScenePaused()
{

}

void MapSelectScene::onSceneFinished()
{

}

