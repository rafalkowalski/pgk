//
//  OpenGl.h
//  mem-game
//
//  Created by Rafał on 17.11.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#ifndef __mem_game__OpenGl__
#define __mem_game__OpenGl__

#include <stdio.h>
#include <GL/glew.h>
#include "Brick.h"
#include <vector>
using namespace std;
class OpenGl {
public:
    
    OpenGl(GLuint pID);
    void draw_ball(float x, float y);
    void draw_paddle(float x);
    void draw_hexagon(int offset);
    void draw_bricks(vector<Brick> bricks);
    
private:
    GLuint programID, ScaleID,MoveXID,MoveYID ,RedID, GreenID, BlueID;
};

#endif /* defined(__mem_game__OpenGl__) */
