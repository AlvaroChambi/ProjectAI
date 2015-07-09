//
//  MessageManager.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "MessageManager.h"

MessageManager::MessageManager()
{

}

void MessageManager::update()
{
    for (Message* message : messageQueue) {
        //dispatch message to the one that are registered
        MessageType type = message->type;
        //Get registered callback for the message type
        for (MessageRegistration* msgRegistration : registrationQueue) {
            if (msgRegistration->type == type) {
                msgRegistration->callback->function(message);
            }
        }
    }
    messageQueue.clear();
}

void MessageManager::registerForMessage(MessageType type, Callback* callback)
{
    registrationQueue.push_back(new MessageRegistration(type, callback));
}

void MessageManager::sendMessage(Message *message)
{
    messageQueue.push_back(message);
}