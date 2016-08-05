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
#include <map>

#include "Point.h"
#include "GameException.h"

template <class T>
class MapLayer {
public:
    MapLayer()
    : width( 0 ), height( 0 ) {
        
    }
    
    MapLayer( const MapLayer& mapLayer )
    : width( mapLayer.width ), height( mapLayer.height ){
        data.resize( width * height );
        typedef typename std::remove_pointer<T>::type A;
        for ( int i = 0; i < mapLayer.data.size(); i++ ) {
            T item = mapLayer.data[i];
            if( item != nullptr ) {
                T newItem = new A( *item );
                data[i] = newItem;
            }
        }
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

    T get( const Point& coord ) const {
        if( coord.isValid( width, height ) ) {
            int i = coord.y * width + coord.x;
            return data.at( i );
        }
        throw IllegalStateException("");
    }
    
    void move( const Point& origin, const Point& destination ) {
        if( origin.isValid( width, height )
            && destination.isValid( width, height ) ) {
            
            if( origin != destination ) {
                T originValue = get( origin );
                
                if( originValue != nullptr
                    && get( destination ) == nullptr ) {
                    set( nullptr, origin );
                    set( originValue, destination );
                } else {
                    throw IllegalStateException("");
                }
            }
        } else {
            throw IllegalStateException("");
        }
    }
    
    T at( int position ) const {
        return data.at( position );
    }
    
    void add( int position, T value ) {
        data[position] = value;
    }
    
    int size() const {
        return (int)data.size();
    }
    
    std::vector<T> data;
    int width;
    int height;
private:
   
};

#endif
