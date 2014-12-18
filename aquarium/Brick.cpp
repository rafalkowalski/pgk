//
//  Brick.cpp
//  mem-game
//
//  Created by Rafał on 15.11.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#include "Brick.h"

Brick::Brick(float s_x, float s_y, float size_x, float size_y, int c){
    position.x = s_x;
    position.y = s_y;
    
    size.x = size_x;
    size.y = size_y;
    color = c;
}