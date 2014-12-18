//
//  Brick.h
//  mem-game
//
//  Created by Rafał on 15.11.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#ifndef __mem_game__Brick__
#define __mem_game__Brick__

#include <stdio.h>
#include <glm/glm.hpp>
class Brick {
public:
    bool destroyed{false};
    Brick(float x, float y, float size_x, float size_y,int c);
    float get_x(){return position.x;}
    float get_y(){return position.y;}
    float left(){return get_x() - size.x/2 ;}
    float right(){return get_x() + size.x/2 ;}
    float top(){return get_y() - size.y/2 ;}
    float bottom(){ return get_y() + size.y/2 ; };
    int color;
private:
    glm::vec2 position;
    glm::vec2 size;
};







#endif /* defined(__mem_game__Brick__) */
