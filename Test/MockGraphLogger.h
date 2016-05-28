//
//  MockGraphLogger.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 27/05/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_MockGraphLogger_h
#define ProjectWar_MockGraphLogger_h

#include "GraphLogger.h"

class MockGraphLogger : public  GraphLogger {
public:
    MOCK_METHOD1( addToPath, void( std::string nodeKey ) );
    MOCK_METHOD0( getIndex, std::string( ) );
    MOCK_METHOD0( nextPath, void() );
    MOCK_METHOD0( getLog, std::string( ) );
};

#endif