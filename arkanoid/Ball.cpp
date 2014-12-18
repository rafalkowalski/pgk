//
//  Ball.cpp
//  mem-game
//
//  Created by Rafał on 13.11.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#include "Ball.h"
#include <vector>
using namespace std;

Ball::Ball(float s_x, float s_y, float d_radius  ,float d_ball_velocity){
    position.x = s_x;
    position.y = s_y;
    radius = d_radius;
    ball_velocity = d_ball_velocity;
    velocity.x = d_ball_velocity;
    velocity.y = -d_ball_velocity;
}

void Ball::update(){
    position  += velocity;
    
    glm::vec2 p1{-0.75, 1.0};
    glm::vec2 p2{0.75, 1.0};
    glm::vec2 p3{1.0, 0.0};
    glm::vec2 p4{0.75,-1.0};
    glm::vec2 p5{-0.75, -1.0};
    glm::vec2 p6{-1.0, 0.0};
    
    vector<glm::vec2> points;
    points.push_back(p1);
    points.push_back(p2);
    points.push_back(p3);
    points.push_back(p4);
    points.push_back(p5);
    points.push_back(p6);
    
    glm::vec2 p, q;
    //ball
    q.x = get_x();
    q.y = get_y();
    glm::vec2 r, s;
    s = velocity;
    
    for(int i = 0; i < points.size(); i++){
        r = points[i%6]-points[(i+1)%6];
        p.x = points[i].x;
        p.y = points[i].y;
        
        float t = cross(q-p, s/(cross(r, s)));
        
        float u = cross(q-p, r / cross(r,s));
        if(t >=-1 && t <= 1 && u <= 1 && u>=-1){
            if(i == 0){
                if(velocity.x > 0 && velocity.y > 0){
                    velocity.x = ball_velocity;
                    velocity.y = -ball_velocity;
                }else {
                    velocity.x = -ball_velocity;
                    velocity.y = -ball_velocity;
                }
            }
            else if(i == 1){
                velocity.x = -velocity.x;
                velocity.y = velocity.y;
            }
            else if(i == 2){
                if(velocity.x > 0 && velocity.y < 0){
                    velocity.x = -ball_velocity;
                    velocity.y = -ball_velocity;
                }else {
                    velocity.x = -ball_velocity;
                    velocity.y = ball_velocity;
                }
                
                
            }
            else if(i == 4){
                if (velocity.x <0 && velocity.y > 0){
                    velocity.x = ball_velocity;
                    velocity.y = ball_velocity;
                }else {
                    velocity.x = ball_velocity;
                    velocity.y = -ball_velocity;
                }
            }
            else if(i == 5){
                if(velocity.x < 0 && velocity.y > 0){
                    velocity.x = ball_velocity ;
                    velocity.y = ball_velocity ;
                }else {
                    velocity.x = ball_velocity ;
                    velocity.y = -ball_velocity ;
                }
            }
        }
    }
}
float Ball::cross(glm::vec2 v1, glm::vec2 v2){
    
    return v1.x*v2.y - v1.y*v2.x;
}
