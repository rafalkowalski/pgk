//
//  Paddle.h
//  mem-game
//
//  Created by Rafał on 13.11.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#ifndef __mem_game__Paddle__
#define __mem_game__Paddle__

#include <stdio.h>
#include <glm/glm.hpp>

class Paddle
{
    
public:
    bool moveLeft = false;
    bool moveRight = false;
    Paddle(float x, float y, float size_x, float size_y ,float paddle_velocity);
    float get_x(){return position.x;}
    float get_y(){return position.y;}
    float left(){return get_x() - size.x/2 ;}
    float right(){return get_x() + size.x/2 ;}
    float top(){return get_y() - size.y/2 ;}
    float bottom(){ return get_y() + size.y/2 ; };
    void update(int key);
    
private:
    glm::vec2 position;
    glm::vec2 velocity;
    glm::vec2 size;
    float paddle_velocity;

    
    
};

#endif /* defined(__mem_game__Paddle__) */
