//
//  PlayerAI.cpp
//  ProjectWar
//
//  Created by Pablo Luis Gutierrez on 09/04/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "PlayerAI.h"
#include "Map.h"
#include "MinimaxAlgorithm.hpp"
#include "Path.h"
#include "DotPath.h"
#include "GameMinimax.h"
#include <stdio.h>
#include <chrono>

PlayerAI::PlayerAI() : Player(), playersList(nullptr)
{
    setType(AI_PLAYER);
}

PlayerAI::PlayerAI(int id, Scene* scene, Renderer* renderer)
        :   Player(id),
            playersList(nullptr),
            scene(scene),
            renderer(renderer)
{
    setType(AI_PLAYER);
}

PlayerAI::~PlayerAI() {

}

void PlayerAI::setPlayerList(std::list<Player*> *players) {
    this->playersList = players;
}


std::list<Command*> PlayerAI::play() {
    std::list<Command*>commands;
    std::chrono::steady_clock::time_point start = std::chrono::steady_clock::now();
    std::cout << "Minimax on progress..." << std::endl;
    executeMinimax();
    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Minimax took "
    << std::chrono::duration_cast<std::chrono::milliseconds>(end - start).count()
    << "ms.\n";
    return commands;
}



void PlayerAI::executeMinimax() {
    Player* enemy = nullptr;
    
    for (Player* player : *playersList) {
        if (this->getId() != player->getId()) {
            enemy = player;
        }
    }
    GameState* game = new GameState( this, enemy, this->getMap() );
    MinimaxAlgorithm* algorithm =
        new MinimaxAlgorithm( new GameMinimax( game ) );
    algorithm->minimax( 4 );
    Movement* movement = (Movement*)algorithm->getBestMove();
    movement->execute();
}

void PlayerAI::testPathfinding(Point origin, Point destination) {
    Path* path = getMap()->getPath(origin, destination);
    path->printPath();
}