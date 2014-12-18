//
//  game.h
//  mem-game
//
//  Created by Rafał on 21.10.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#ifndef __mem_game__game__
#define __mem_game__game__

#include <stdio.h>
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
class Game
{
public:
    void initGame(GLFWwindow* window);
    int initGlfw(GLFWwindow* window);
};

#endif /* defined(__mem_game__game__) */
