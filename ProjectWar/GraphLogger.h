//
//  GraphLogger.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 27/05/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_GraphLogger_h
#define ProjectWar_GraphLogger_h

class GraphLogger {
public:
    virtual std::string getLog() = 0;
    virtual void addToPath( std::string nodeKey ) = 0;
    virtual std::string getIndex() = 0;
    virtual void nextPath() = 0;
};

#endif
