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
#include "ProjectedLayout.h"
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
    Texture* quad = renderer->loadShape(RECTANGLE, Color(255,0,0), 100, 100);
    Texture* quad1 = renderer->loadShape(RECTANGLE, Color(0,255,0), 100, 100);
    Texture* quad2 = renderer->loadShape(RECTANGLE, Color(0,0,255), 100, 100);
    
    UIComponent* item = new UIComponent;
    item->params.width = WRAP;
    item->params.height = WRAP;
    item->weight = 1;
    
    item->texture = quad2;
    
    UIComponent* item1 = new UIComponent;
    item1->params.width = WRAP;
    item1->params.height = WRAP;
    item1->params.marginTop = 10;
    item1->params.marginDown = 10;
    item1->params.marginLeft = 20;
    item1->params.marginRight = 20;
    item1->weight = 1;
    
    item1->texture = quad1;
    
    UIComponent* item2 = new UIComponent;
    item2->params.width = WRAP;
    item2->params.height = WRAP;
    item2->weight = 1;
    
    item2->texture = quad2;
    
    UIComponent* item3 = new UIComponent;
    item3->params.width = WRAP;
    item3->params.height = WRAP;
    item3->weight = 1;
    
    item3->texture = quad;
    
    UIComponent* item4 = new UIComponent;
    item4->params.width = WRAP;
    item4->params.height = WRAP;
    item4->weight = 1;
    
    item4->texture = quad1;
    
    ProjectedLayout* projectedlayout = new ProjectedLayout;
    HorizontalLayout* depth0Layout = new HorizontalLayout;
    depth0Layout->params.disposition = WEIGHT_DISPOSITION;
    Layout* depth1Layout= new Layout;
    Layout* depth2Layout = new Layout;
    
    
    //this->setUIHUD(projectedlayout);
    
    projectedlayout->addComponent(depth0Layout);
    projectedlayout->addComponent(depth1Layout);
    projectedlayout->addComponent(depth2Layout);
    
    depth0Layout->addComponent(item1);
    depth0Layout->addComponent(item2);
    
    depth1Layout->addComponent(item3);
    depth1Layout->addComponent(item4);
    
    depth2Layout->addComponent(item);
    
    Layout* layout = new Layout();
    layout->params = Params(200,200,CENTER);
    
    this->setUIHUD(layout);
}

void MapSelectScene::onScenePaused()
{

}

void MapSelectScene::onSceneFinished()
{

}

