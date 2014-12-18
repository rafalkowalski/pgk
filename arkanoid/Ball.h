//
//  Ball.h
//  mem-game
//
//  Created by Rafał on 13.11.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#ifndef __mem_game__Ball__
#define __mem_game__Ball__

#include <stdio.h>
#include <glm/glm.hpp>
#include <vector>
class Ball
{
    
public:
    
    Ball(float x, float y, float radius  ,float ball_velocity);
    glm::vec2 velocity;
    
    float get_x(){return position.x;}
    float get_y(){return position.y;}
    void set_y(float p){position.y = p;}
    float left(){return get_x() - radius ;}
    float right(){return get_x() + radius ;}
    float top(){return get_y() - radius ;}
    float bottom(){ return get_y() + radius ; };
    void update();
    float cross(glm::vec2 v1, glm::vec2 v2);
    
private:
    glm::vec2 position;
    
    float radius, ball_velocity;

    
};

#endif /* defined(__mem_game__Ball__) */
