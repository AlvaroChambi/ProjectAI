//
//  GameException.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 23/5/16.
//  Copyright © 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef GameException_h
#define GameException_h

#include <iostream>
#include <exception>
#include <stdexcept>
#include <sstream>

class InvalidPositionException : public std::runtime_error {
public:
    InvalidPositionException( int x, int y, int width, int height )
    : runtime_error( "Invalid position: " ), x( x ), y( y ),
    width( width ), height( height )
    {}
    
    virtual const char* what() const throw() {
        std::ostringstream message;
        message << std::runtime_error::what() << " ";
        message << " ( " << x << ", " << y << " ) " << " width: " << width << " height: " << height;
        return message.str().c_str();
    }
private:
    int x;
    int y;
    int width;
    int height;
};
        
class IllegalStateException : public std::runtime_error {
public:
    IllegalStateException( std::string msg )
    : runtime_error( "Illegal state: " ), msg( msg ) {}
    
    virtual const char* what() const throw() {
        std::ostringstream message;
        message << std::runtime_error::what() << " ";
        message << msg;
        return message.str().c_str();
    }
private:
    std::string msg;
};
        
class EndOfIteratorException : public std::runtime_error {
public:
    EndOfIteratorException( int currentPosition, int width, int height )
    : runtime_error( "End of iterator reached: " ),
    currentPosition( currentPosition ), width( width ), height( height ) {}
    
    virtual const char* what() const throw() {
        std::ostringstream message;
        message << std::runtime_error::what() << " ";
        message << "current position " << currentPosition << " width " << width
            << " height " << height;
        return message.str().c_str();
    }
private:
    int currentPosition;
    int width;
    int height;
};

#endif /* GameException_h */
