//
//  player.h
//  mem-game
//
//  Created by Rafał on 10.12.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#ifndef __mem_game__player__
#define __mem_game__player__

#include <stdio.h>
#include <glm/glm.hpp>
#include <vector>
#include "Bubble.h"
using namespace std;
class Player
{
    
public:
    
    Player(float x, float y, float z);
    
    float get_x(){return position.x;}
    float get_y(){return position.y;}
    float get_z(){return position.z;}
    float get_radius(){return radius;}
    void set_y(float p){position.y = p;}
    void update();
    int key;
    void reset();
    glm::vec3 get_position(){return position;}
    bool check_collision(Bubble &bubble);
    
private:
    glm::vec3 position;
    float radius, bubble_velocity;
};


#endif /* defined(__mem_game__player__) */
