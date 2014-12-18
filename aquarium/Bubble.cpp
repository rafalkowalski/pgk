//
//  Ball.cpp
//  mem-game
//
//  Created by Rafał on 13.11.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#include "Bubble.h"
#include <vector>
using namespace std;

Bubble::Bubble(float s_x, float s_y, float s_z){
    
    float value = 0.01+(rand() % 20 + 1)*0.01;
    position.x = s_x;
    position.y = s_y;
    position.z = s_z;
    radius = value;
    bubble_velocity = 0.01;
    tmp_radius = radius;
}

void Bubble::update(){
    position.y += bubble_velocity;
    if(tmp_radius * 1.1 > radius){
        radius = radius+0.0002;

    }
}

void Bubble::reset(){
    position.y  = -1;
    if(tmp_radius * 1.1 > radius){
        radius = tmp_radius;
    }
}

void Bubble::stop(){
    bubble_velocity = 0;
}


