//
//  MockOption.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 26/5/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef MockOption_h
#define MockOption_h

#include "gmock/gmock.h"
#include "Option.h"

class MockOption : public  Option {
public:
    MOCK_METHOD0( execute, void() );
    MOCK_METHOD0( cancel, void() );
};

#endif /* MockOption_h */
