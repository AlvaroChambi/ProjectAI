//
//  MessageRegistration.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__MessageRegistration__
#define __ProjectWar__MessageRegistration__

#include <stdio.h>
#include "Message.h"
#include "Callback.h"

class MessageRegistration
{
public:
    MessageRegistration(MessageType type, Callback* callback) : type(type), callback(callback)
    {
    
    }
    ~MessageRegistration(){}
    
    MessageType type;
    Callback* callback;
};

#endif /* defined(__ProjectWar__MessageRegistration__) */
