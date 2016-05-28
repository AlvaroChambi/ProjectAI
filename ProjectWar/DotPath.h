//
//  DotPath.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 27/05/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_DotPath_h
#define ProjectWar_DotPath_h

#include <vector>
#include <string>
#include "GraphLogger.h"

class DotPath {
public:
    DotPath();
    ~DotPath();
    
    void addNode( std::string nodeKey );
    std::string getLine();
private:
    const std::string LINK = "--";
    std::vector<std::string> nodes;
};

class DotFile {
public:
    DotFile();
    ~DotFile();
    
    std::string getFile();
    void addPath( DotPath* dotPath );
private:
    std::vector<DotPath*> paths;
};

class DotBuilder : public GraphLogger {
public:
    DotBuilder();
    ~DotBuilder();
    
    DotFile* getDotFile();
    void addToPath( std::string nodeKey );
    std::string getIndex();
    void nextPath();
    std::string getLog();
private:
    DotFile* dotFile;
    DotPath* currentPath;
    int index;
};

#endif
