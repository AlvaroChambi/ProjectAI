//
//  DotPath.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 27/05/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//
#include "DotPath.h"

DothPath::DotPath() {

}

DotPath::~DotPath() {

}

void DotPath::addNode( std::string nodeKey ) {
    nodes.push_back( nodeKey );
}

std::string DotPath::getLine() {
    std::string line = "";
    for( int i = 0; i < nodes.size(); i++ ) {
        std::string nodeKey = nodes.at( i );
        if( i-1 == nodes.size()  ) {
            line = line + nodeKey
        }
        line = line + nodeKey + LINK;
    }
    return line;
}

DotFile::DotFile() {

}

DotFile::~DotFile() {

}

void DotFile::addPath( DotPath *dotPath ) {
    paths.push_back( dotPath );
}

std::string DotFile::getDotFile() {
    std::string file = "";
    for ( DotPath* path : paths ) {
        file = file + path->getLine() + "\n";
    }
}

DotBuilder::DotBuilder() {
    dotFile = new DotFile;
    currentPath = new DotPath;
}

DotBuilder::~DotBuilder() {

}

void DotBuilder::addToPath( std::string nodeKey ) {
    currentPath->addNode( nodeKey );
}

void DotBuilder::nextPath() {
    dotFile->addPath( currentPath );
    currentPath = new DotPath;
}