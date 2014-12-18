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
class Bubble
{
    
public:
    
    Bubble(float x, float y, float z);
    
    float get_x(){return position.x;}
    float get_y(){return position.y;}
    float get_z(){return position.z;}
    float get_radius(){return radius;}
    void set_y(float p){position.y = p;}
    void update();
    void reset();
    int i_start;
    int i_end;
    void stop();
    bool active = false;
    glm::vec3 get_position(){return position;}
private:
    glm::vec3 position;
    float radius, bubble_velocity, tmp_radius;
};

#endif /* defined(__mem_game__Ball__) */
