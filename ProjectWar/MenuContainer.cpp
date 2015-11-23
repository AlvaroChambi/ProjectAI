//
//  MenuContainer.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 15/9/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "MenuContainer.h"

MenuContainer::MenuContainer()
{
    UIComponent* component = new UIComponent;
    root = boost::add_vertex(component, customGraph);
}

MenuContainer::~MenuContainer()
{

}

void MenuContainer::addToRoot(UIComponent *newNode)
{
    CustomVertex vertex = boost::add_vertex(newNode, customGraph);
    boost::add_edge(root, vertex, customGraph);
}

void MenuContainer::addNode(UIComponent *newNode, UIComponent *parent)
{
    CustomVertex vertex = boost::add_vertex(newNode, customGraph);
    CustomVertex parentVertex = getVertex(parent);
    
    boost::add_edge(parentVertex, vertex, customGraph);
}

std::vector<UIComponent*> MenuContainer::getChilds(UIComponent *node)
{
    std::vector<UIComponent*> childs;
    CustomGraph::out_edge_iterator outStart, outEnd;
    IndexMap index = boost::get(boost::vertex_index, customGraph);
    CustomVertex vertex = getVertex(node);
    
    for (std::tie(outStart, outEnd) =  boost::out_edges(vertex, customGraph); outStart != outEnd; ++outStart) {
        std::cout << "(" << index[source(*outStart,customGraph)] << "," << index[target(*outStart,customGraph)] << ") ";
        CustomVertex vertex = index[target(*outStart,customGraph)];
        CustomGraph::vertex_bundled component = customGraph[vertex];
        childs.push_back(component);
    }
    return childs;
}

MenuContainer::CustomVertex MenuContainer::getVertex(UIComponent *component)
{
    CustomVertex vertex = 0;
    std::pair<CustomGraph::vertex_iterator, CustomGraph::vertex_iterator> pair;
    
    for (pair = boost::vertices(customGraph); pair.first != pair.second; ++pair.first) {
        MenuContainer::CustomGraph::vertex_bundled bundle = customGraph[*pair.first];
        if (bundle == component) {
            vertex = *pair.first;
        }
    }
    
    return vertex;
}

std::vector<UIComponent*> MenuContainer::getRootChilds()
{
    std::vector<UIComponent*> childs;
    
    CustomGraph::out_edge_iterator outStart, outEnd;
    IndexMap index = boost::get(boost::vertex_index, customGraph);
    
    for (std::tie(outStart, outEnd) =  boost::out_edges(root, customGraph); outStart != outEnd; ++outStart) {
        std::cout << "(" << index[source(*outStart,customGraph)] << "," << index[target(*outStart,customGraph)] << ") ";
        CustomVertex vertex = index[target(*outStart,customGraph)];
        CustomGraph::vertex_bundled component = customGraph[vertex];
        childs.push_back(component);
    }
    return childs;
}