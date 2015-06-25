//
//  MessageManager.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__MessageManager__
#define __ProjectWar__MessageManager__

#include <stdio.h>
#include <list>
#include "MessageRegistration.h"

class MessageManager
{
public:
    static MessageManager& getInstance()
    {
        static MessageManager* instance = new MessageManager;
        return *instance;
    }
    
    void update();
    void registerForMessage(MessageType type, Callback* callback);
    void sendMessage(Message* message);
    
private:
    MessageManager();
    
    std::list<Message*> messageQueue;
    std::list<MessageRegistration*> registrationQueue;
};

#endif /* defined(__ProjectWar__MessageManager__) */
