//
//  OpenGl.cpp
//  mem-game
//
//  Created by Rafał on 17.11.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#include "OpenGl.h"
#include "colors.h"
OpenGl::OpenGl(GLuint pId ){
    programID = pId;
    ScaleID = glGetUniformLocation(programID, "scale");
    MoveXID = glGetUniformLocation(programID, "move_x");
    MoveYID = glGetUniformLocation(programID, "move_y");
    
    RedID = glGetUniformLocation(programID, "red");
    GreenID = glGetUniformLocation(programID, "green");
    BlueID = glGetUniformLocation(programID, "blue");
}

void OpenGl::draw_ball(float x,float y){
    glUniform1f(MoveXID, x);
    glUniform1f(MoveYID, y);
    glUniform1f(ScaleID,1.0);
    glUniform1f(RedID,0.0);
    glUniform1f(GreenID,0.0);
    glUniform1f(BlueID,0.0);
    glDrawArrays(GL_TRIANGLE_FAN, 4, 364);
}

void OpenGl::draw_paddle(float x){
    glUniform1f(MoveXID, x);
    glUniform1f(MoveYID, 0.0);
    glUniform1f(ScaleID,1.0);
    glUniform1f(RedID,1.0);
    glUniform1f(GreenID,0.0);
    glUniform1f(BlueID,0.4);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
}

void OpenGl::draw_hexagon(int g_hexagonOffset){
    glUniform1f(MoveXID, 0.0);
    glUniform1f(MoveYID, 0.0);
    glUniform1f(ScaleID,1.0);
    glUniform1f(RedID,0.8);
    glUniform1f(GreenID,0.6);
    glUniform1f(BlueID,0.2);
    glDrawArrays(GL_TRIANGLE_STRIP, g_hexagonOffset, 18);
}

void OpenGl::draw_bricks(vector<Brick> bricks){
    glUniform1f(MoveXID, 0.0);
    glUniform1f(MoveYID, 0.0);
    glUniform1f(ScaleID,1.0);
    for (int i=0 ; i < 36 * 4; i+=4){
        if(bricks[i/4].destroyed)
            continue;
        Colors colors;
        vector<float> color = colors.get_colors(bricks[i/4].color);
        glUniform1f(RedID, color[0]);
        glUniform1f(GreenID, color[1]);
        glUniform1f(BlueID, color[2]);
        
        glDrawArrays(GL_TRIANGLE_STRIP, 367 + i , 4);
    }
}
