//
//  Message.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 11/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__Message__
#define __ProjectWar__Message__

#include <stdio.h>


enum MessageType
{
    MESSAGE_NOT_DEFINED,
    MESSAGE_SHOW_POPUP,
    MESSAGE_HIDE_POPUP,
};

class Message
{
public:
    Message(MessageType type) : type(MESSAGE_NOT_DEFINED)
    {
        this->type = type;
    }
    
    ~Message(){}
    
    MessageType type;
};

#endif /* defined(__ProjectWar__Message__) */
