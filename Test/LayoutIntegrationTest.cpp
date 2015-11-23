//
//  LayoutIntegrationTest.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 8/9/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "LayoutIntegrationTest.h"
#include "VerticalLayout.h"
#include "ProjectedLayout.h"
#include "HorizontalLayout.h"
#include "Node.h"
#include "MenuContainer.h"
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>


LayoutIntegrationTest::LayoutIntegrationTest(Renderer* renderer, SceneManager* sceneManager) : Scene(renderer, sceneManager)
{

}

LayoutIntegrationTest::~LayoutIntegrationTest()
{

}

void LayoutIntegrationTest::onSceneStarted()
{
    Texture* quad = renderer->loadSprite("a_bubble.png", 100, 100);
    Texture* quad1 = renderer->loadSprite("b_bubble.png", 100, 100);
    Texture* quad2 = renderer->loadSprite("c_bubble.png", 100, 100);
    Texture* quad3 = renderer->loadSprite("d_bubble.png", 100, 100);
    Texture* quad4 = renderer->loadSprite("e_bubble.png", 100, 100);
    Texture* quad5 = renderer->loadSprite("f_bubble.png", 100, 100);
    
    UIComponent* item = new UIComponent;
    item->params.width = WRAP;
    item->params.height = WRAP;
    item->weight = 1;
    
    item->texture = quad;
    
    UIComponent* item1 = new UIComponent;
    item1->params.width = WRAP;
    item1->params.height = WRAP;
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
    
    item3->texture = quad3;
    
    UIComponent* item4 = new UIComponent;
    item4->params.width = WRAP;
    item4->params.height = WRAP;
    item4->weight = 1;
    
    item4->texture = quad4;
    
    UIComponent* item5 = new UIComponent;
    item5->params.width = WRAP;
    item5->params.height = WRAP;
    item5->weight = 1;
    
    item5->texture = quad5;
 
    ProjectedLayout* projectedlayout = new ProjectedLayout;
    
    MenuContainer* menuContainer = new MenuContainer;
    //maybe add trigger and not add to root
    menuContainer->addToRoot(item);
    menuContainer->addToRoot(item1);
    
    menuContainer->addNode(item2, item1);
    menuContainer->addNode(item3, item1);
    
    menuContainer->addNode(item4, item2);
    menuContainer->addNode(item5, item2);
    
    //Graph building end
    projectedlayout->menuContainer = menuContainer;
    
    this->setUIHUD(projectedlayout);
}

void LayoutIntegrationTest::onScenePaused()
{

}

void LayoutIntegrationTest::onSceneFinished()
{

}


