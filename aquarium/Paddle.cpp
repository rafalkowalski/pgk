//
//  Paddle.cpp
//  mem-game
//
//  Created by Rafał on 13.11.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#include "Paddle.h"
#define LEFT 0
#define RIGHT 1

Paddle::Paddle(float s_x, float s_y, float size_x, float size_y ,float p_v){
    paddle_velocity = p_v;
    velocity.y =0;
    position.x = s_x;
    position.y = s_y;
    
    size.x = size_x;
    size.y = size_y;
}

void Paddle::update(int key){
    position  += velocity;
    
    if(moveLeft && left() > -0.85) {
        velocity.x = -paddle_velocity;
    }
    else if(moveRight
            && right() < 0.85) {velocity.x = paddle_velocity;}
    
    else velocity.x = 0;
}