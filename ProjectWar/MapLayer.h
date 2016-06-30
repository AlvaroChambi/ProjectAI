//
//  MapLayer.h
//  ProjectWar
//
//  Created by Alvaro Chambi Campos on 29/06/16.
//  Copyright (c) 2016 Alvaro Chambi Campos. All rights reserved.
//

#ifndef ProjectWar_MapLayer_h
#define ProjectWar_MapLayer_h

#include <vector>
#include "Point.h"
#include "GameException.h"

template <class T>
class MapLayer {
public:
    MapLayer()
    : width( 0 ), height( 0 ) {
        
    }
    ~MapLayer() {
        data.clear();
    }

    void resize( int width, int height ) {
        if( width > 0 && height > 0 ) {
            this->width = width;
            this->height = height;
            data.resize( width*height, nullptr );
        } else {
            throw IllegalStateException("");
        }
    }

    void set( const T value, const Point& coord ) {
        if( coord.isValid( width, height ) ) {
            int i = coord.y * width + coord.x;
            data[i] = value;
        } else {
            //Illegal state exception
        }
    }

    T get( const Point &coord ) {
        if( coord.isValid( width, height ) ) {
            int i = coord.y * width + coord.x;
            return data.at( i );
        }
        throw IllegalStateException("");
    }
    
    void move( const Point& origin, const Point& destination ) {
        if( origin.isValid( width, height )
            && destination.isValid( width, height ) ) {
            T originValue = get( origin );
            
            if( originValue != nullptr && get( destination ) == nullptr ) {
                set( nullptr, origin );
                set( originValue, destination );
            } else {
                throw IllegalStateException("");
            }
        } else {
            throw IllegalStateException("");
        }
    }
    
    T at( int position ) {
        return data.at( position );
    }
    
    int size() {
        return data.size();
    }
private:
    std::vector<T> data;
    int width;
    int height;
};

#endif
