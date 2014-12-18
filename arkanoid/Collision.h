//
//  Colission.h
//  mem-game
//
//  Created by Rafał on 18.11.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#ifndef __mem_game__Colission__
#define __mem_game__Colission__

#include <stdio.h>
#include "Paddle.h"
#include "Ball.h"
#include "Brick.h"
class Collision {
public:
    Collision(float ball_velocity);
    void test_collision(Paddle &paddle, Ball &ball, float ball_velocity);
    bool is_intersecting(Paddle &paddle, Ball &ball);
    bool is_intersecting(Brick &brick, Ball &ball);
    void test_collision(Brick &brick, Ball &ball);
private:
    float ball_velocity;
};

#endif /* defined(__mem_game__Colission__) */
