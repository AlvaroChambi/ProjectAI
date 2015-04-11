//
//  UnitUIView.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 4/4/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "UnitUIView.h"
#include "Button.h"
#include "ProjectAI.h"

UnitUIView::UnitUIView() : Layout(-1), unit(nullptr)
{

}

UnitUIView::UnitUIView(int id) : Layout(id), unit(nullptr)
{

}

UnitUIView::~UnitUIView()
{

}

void UnitUIView::setModel(Model *model)
{
    model->registerObserver(this);
    this->unit = (Unit*)model;
}

void UnitUIView::update(Update update)
{
    switch (update) {
        case COMMANDS_UPDATE:
            updateComponents();
            break;
        default:
            break;
    }
}

//for each command instantiate a button
void UnitUIView::updateComponents()
{
    this->cleanComponents();
    
    for (int i = 0; i < unit->getNumCommands(); i++) {
        Button* button;
        switch (unit->getCommand(i)) {
            case ATTACK:
                button = new Button(ProjectAI::ATTACK_BUTTON);
                button->setImageResource("attack_button.bmp");
                break;
            case WAIT:
                button = new Button(ProjectAI::WAIT_BUTTON);
                button->setImageResource("wait_button.bmp");
                break;
            case CANCEL:
                button = new Button(ProjectAI::CANCEL_BUTTON);
                button->setImageResource("cancel_button.bmp");
                break;
            case END:
                button = new Button(ProjectAI::END_BUTTON);
                button->setImageResource("end_button.bmp");
                break;
            case CAPTURE:
                button = new Button(ProjectAI::CAPTURE_BUTTON);
                button->setImageResource("capture_button.png");
                break;
            default:
                break;
        }
        button->setParams(Params(60,40,CENTER));
        this->addComponent(button);
    }
    this->updatePosition();
}

void UnitUIView::updatePosition()
{
    UIComponent::updatePosition();
    if(components.getSize() > 0){
        int subParentWidth = getWidth() / components.getSize();
        
        for (int i = 0; i < components.getSize(); i++) {
            int subParentX = getPosition().x + subParentWidth * i;
            Point subParentPosition = Point(subParentX, getPosition().y);
            components.getElement(i)->center(subParentPosition, subParentWidth, getHeight());
        }
        
    }
}
