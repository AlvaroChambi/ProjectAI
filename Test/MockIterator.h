//
//  MockIterator.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 8/6/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef MockIterator_h
#define MockIterator_h

#include "gmock/gmock.h"
#include "Iterator.h"

class MockIterator : public  Iterator {
public:
    MOCK_METHOD0( hasNext, bool() );
    MOCK_METHOD0( next, Point() );
    MOCK_METHOD1( isValid, bool( Point position ) );
};


#endif /* MockIterator_h */
