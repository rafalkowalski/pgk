//
//  player.cpp
//  mem-game
//
//  Created by Rafał on 10.12.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#include "player.h"
#include <vector>
using namespace std;
#define STOP 6
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define TOP 4
#define BOTTOM 5

Player::Player(float s_x, float s_y, float s_z){
    
    position.x = s_x;
    position.y = 0.0;
    position.z = s_z;
    radius = 0.1;
    bubble_velocity = 0.01;
    key = 6;
}

void Player::update(){
    if(key == UP){
        position.x  += bubble_velocity;
    } else if(key == DOWN && 0.0 < (get_x()-radius)){
        position.x  -= bubble_velocity;
    } else if(key == LEFT && -1.0 < (get_z()-radius)){
        position.z  -= bubble_velocity;
    }
    else if(key == RIGHT && 1.0 > (get_z()+radius)){
        position.z  += bubble_velocity;
    }
    else if(key == TOP  && 1.0 >(get_y()+radius)){
        position.y  += bubble_velocity;
    }
    else if(key == BOTTOM && -1.0 < (get_y()-radius)){
        position.y  -= bubble_velocity;
    }

}

void Player::reset(){
    position.x = -2;
}

bool Player::check_collision(Bubble &bubble){
    float d = glm::distance(get_position(), bubble.get_position());
    if(abs(d) < get_radius() + bubble.get_radius()){
       
        return true;
    }else{
        return false;
    }
}