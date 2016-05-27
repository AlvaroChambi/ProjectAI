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
    
    std::string getDotFile();
    void addPath( DotPath* dotPath );
private:
    std::vector<DotPath*> paths;
};

class DotBuilder {
public:
    DotBuilder();
    ~DotBuilder();
    
    void addToPath( std::string nodeKey );
    void nextPath();
private:
    DotFile* dotFile;
    DotPath* currentPath;
};

#endif
