//
//  MenuContainer.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 15/9/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#ifndef __ProjectWar__MenuContainer__
#define __ProjectWar__MenuContainer__

#include <stdio.h>
#include <vector>
#include "UIComponent.h"
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>

class MenuContainer
{
public:
    typedef boost::adjacency_list<boost::vecS,boost::vecS,boost::directedS, UIComponent*> CustomGraph;
    typedef boost::graph_traits<CustomGraph>::vertex_descriptor CustomVertex;
    typedef boost::graph_traits<CustomGraph>::edge_descriptor CustomEdge;
    
    typedef boost::graph_traits<CustomGraph>::out_edge_iterator OutEdgeIterator;
    
    typedef boost::property_map<CustomGraph, boost::vertex_index_t>::type IndexMap;
    
    MenuContainer();
    virtual ~MenuContainer();
    
    void addToRoot(UIComponent* newNode);
    void addNode(UIComponent* newNode, UIComponent* parent);
    std::vector<UIComponent*> getChilds(UIComponent* node);
    std::vector<UIComponent*> getRootChilds();
    
    CustomVertex getVertex(UIComponent* component);
    
    CustomVertex root;
    CustomGraph customGraph;
};

#endif /* defined(__ProjectWar__MenuContainer__) */
