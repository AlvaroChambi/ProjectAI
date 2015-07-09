//
//  DataMessage.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 29/6/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__DataMessage__
#define __ProjectWar__DataMessage__

#include <iostream>
#include "Message.h"

template <class T>
class DataMessage : public Message
{
public:
    DataMessage(MessageType type, T dataStorage) : Message(type)
    {
        this->dataStorage = dataStorage;
    }
    virtual ~DataMessage()
    {}
    
    T dataStorage;
    
};

#endif /* defined(__ProjectWar__DataMessage__) */
