//
//  Unit.cpp
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 13/3/15.
//  Copyright (c) 2015 Alvaro Chambi Campos. All rights reserved.
//

#include "Unit.h"
#include "Map.h"
#include "Player.h"
#include "MoveCommand.h"
#include "AttackCommand.h"
#include "CaptureCommand.h"
#include "GameException.h"
#include "UnitFilter.h"
#include "AreaIterator.h"
#include "GameState.h"

Unit::Unit()
: Model(), tile(), movement(0), hp(0),
  active(true), commands(), attackRange(0), ownerID( -1 ) {
    
}

Unit::~Unit()
{

}

//This method does not update the texture position, maybe we have to implement it
void Unit::setPosition(int x, int y)
{
    this->tile.position.x = x;
    this->tile.position.y = y;
}

void Unit::setPosition(const Tile tile)
{
    this->tile = tile;
    this->notifyObservers(POSITION_UPDATE);
}

void Unit::setMovement(int movement)
{
    this->movement = movement;
}

int Unit::getMovement() const{
    return movement;
}

void Unit::setActive(bool active)
{
    this->active = active;
    this->notifyObservers(ACTIVE_UPDATE);
}

bool Unit::isActive()
{
    return active;
}

void Unit::setSelected(bool selected)
{
    this->selected = selected;
    this->notifyObservers(SELECTED_UPDATE);
}

bool Unit::isSelected()
{
    return selected;
}

Tile Unit::getTile()
{
    return tile;
}

Point Unit::getPosition() const {
    return tile.position;
}

void Unit::setAttackRange( int attackRange ) {
    this->attackRange = attackRange;
}

int Unit::getAttackRange() const {
    return attackRange;
}

void Unit::setHP( int hp)  {
    this->hp = hp;
    this->notifyObservers(HP_UPDATE);
}

int Unit::getHP() const {
    return hp;
}

void Unit::updateCommands( std::vector<UnitCommand> commands ) {
    //Clean previous commands and set the new ones
    this->commands = commands;
    this->notifyObservers(COMMANDS_UPDATE);
}

void Unit::addCommand(UnitCommand command)
{
    commands.push_back(command);
}

UnitCommand Unit::getCommand( int position ) {
    return commands.at( position  );
}

int Unit::getNumCommands() {
    return (int)commands.size();
}

//TODO duplicated code here...
bool Unit::canReach(Point destination)
{
    bool result = false;
    int distance = std::abs(destination.x - this->getPosition().x) +
                    std::abs(destination.y - this->getPosition().y);
    if (distance <= movement) {
        result = true;
    }
    return result;
}

bool Unit::canAttack(Point destination)
{
    bool result = false;
    int distance = std::abs(destination.x - this->getPosition().x) +
                    std::abs(destination.y - this->getPosition().y);
    
    if (distance <= attackRange) {
        result = true;
    }
    return result;
}

//Movement added to the attack to know if the unit can attack the targeted unit in this turn
bool Unit::canAttack(Unit* unit)
{
    bool result=false;
    Point destination = unit->getPosition();
    int distance = std::abs(destination.x - this->getPosition().x) +
    std::abs(destination.y - this->getPosition().y);
    
    if (distance <= attackRange + movement) {
        result = true;
    }
    return result;
}

bool Unit::onRange( const Point& destination, int range ) const {
    int distance = tile.position.distance( destination );
    if( distance <= range ) {
        return true;
    }
    return false;
}

std::vector<Action*>* Unit::getAttackActions( IMap *map,
                                             std::vector<Unit *> targets,
                                             GameState& gameState ) {
    std::vector<Action*>* attackActions = new std::vector<Action*>;
    
    int range = getMovement() + getAttackRange();
    for ( Unit* target : targets ) {
        if( this->onRange( target->getPosition() , range ) ) {
            AreaIterator* areaIterator = new AreaIterator;
            areaIterator->buildArea( tile.position,
                                    getMovement(),
                                    MAP_WIDTH, MAP_HEIGHT );
            Iterator* unitMoveIterator =
            new UnitMovementFilter( *areaIterator,(Map*)map, *this );
            
            while ( unitMoveIterator->hasNext() ) {
                Point destination = unitMoveIterator->next();
                if( target->onRange( destination , getAttackRange() )
                   && !gameState.isInvalidated( destination ) ) {
                    
                    gameState.addToInvalidated( destination );
                    Action* action = new Action;
                    MoveCommand* move =
                    new MoveCommand( *this, map, destination );
                    AttackCommand* attack =
                    new AttackCommand( this, target, (Map*)map );
                    
                    action->commands.push_back( move );
                    action->commands.push_back( attack );
                    attackActions->push_back( action );
                }
            }
        }
    }
    
    return attackActions;

}

std::vector<Action*>* Unit::getCaptureActions( IMap *map, Player *player,
                                        std::vector<Building *> targets,
                                        GameState& gameState ) {
    std::vector<Action*>* captureActions = new std::vector<Action*>;
    
    for ( Building* building : targets ) {
        if( onRange( building->getPosition() , getMovement() )
           && !building->isCaptured( player->getId() )
           && !gameState.isInvalidated( building->getPosition() ) ) {
            
            if( getPosition() == building->getPosition() ) {
                addCaptureCommand( gameState, building, map,
                                  captureActions, player );
            } else if ( map->isValidPosition( building->getPosition() ) ) {
                addCaptureCommand( gameState, building, map,
                                  captureActions, player );
            }
        }
    }
    
    return captureActions;
}

void Unit::addCaptureCommand( GameState &gameState, Building *building,
                             IMap *map, std::vector<Action *> *captureActions,
                             Player* player ) {
    gameState.addToInvalidated( building->getPosition() );
    
    Action* action = new Action;
    MoveCommand* moveCommand = new MoveCommand( *this, (Map*)map,
                                               building->getPosition() );
    CaptureCommand* captureCommand = new CaptureCommand( player,
                                                        this, building );
    
    action->commands.push_back( moveCommand );
    action->commands.push_back( captureCommand );
    captureActions->push_back( action );
}

void Unit::updateState() {
    this->notifyObservers(STATE_UPDATE);
}

void Unit::setOwnerID( int ownerID ) {
    this->ownerID = ownerID;
}

int Unit::getOwnerID() const {
    return ownerID;
}