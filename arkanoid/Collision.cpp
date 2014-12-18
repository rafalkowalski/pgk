//
//  Colission.cpp
//  mem-game
//
//  Created by Rafał on 18.11.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#include "Collision.h"
#include "Paddle.h"
#include "Ball.h"

Collision::Collision(float b_velocity){
    ball_velocity = b_velocity;
}

void Collision::test_collision(Paddle &paddle, Ball &ball,float ball_velocity){
    int rand_value = rand() % 3;
    float val = rand_value * 0.001;
    if(!is_intersecting(paddle, ball))
        return;
    
    ball.velocity.y = ball.get_y() > paddle.get_y() ? ball_velocity : val -ball_velocity;
    float val1 = rand_value * 0.001;
    if(ball.get_x() < paddle.get_x()) ball.velocity.x = val1-ball_velocity;
    else ball.velocity.x = val1 + ball_velocity;
}

bool Collision::is_intersecting(Paddle &paddle, Ball &ball){
        return 	paddle.right() >= ball.left() &&
                paddle.left() <= ball.right() &&
                paddle.bottom() >= ball.top() &&
                paddle.top() <= ball.bottom();
}

bool Collision::is_intersecting(Brick &brick, Ball &ball){
        return 	brick.right() >= ball.left() &&
                brick.left() <= ball.right() &&
                brick.bottom() >= ball.top() &&
                brick.top() <= ball.bottom();
}

void Collision::test_collision(Brick &brick, Ball &ball)
{
    if(brick.destroyed)
        return;
    
    if(!is_intersecting(brick, ball)) return;
    
    brick.color= brick.color-1;
    if(brick.color < 1){
        brick.destroyed = true;
    }
    
    float overlapLeft{ball.right() - brick.left()};
    float overlapRight{brick.right() - ball.left()};
    float overlapTop{ball.bottom() - brick.top()};
    float overlapBottom{brick.bottom() - ball.top()};
    
    bool ballFromLeft(abs(overlapLeft) < abs(overlapRight));
    bool ballFromTop(abs(overlapTop) < abs(overlapBottom));
    float minOverlapX{ballFromLeft ? overlapLeft : overlapRight};
    float minOverlapY{ballFromTop ? overlapTop : overlapBottom};
    if(abs(minOverlapX) < abs(minOverlapY))
        ball.velocity.x = ballFromLeft ? -ball_velocity : ball_velocity;
    else
        ball.velocity.y = ballFromTop ? -ball_velocity : ball_velocity;
    
}