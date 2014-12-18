//
//  setup.h
//  mem-game
//
//  Created by Rafał on 24.10.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#ifndef __mem_game__setup__
#define __mem_game__setup__

#include <stdio.h>
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
class Setup{
public:
    GLFWwindow* get_window();
    void init();
    
private:
    GLFWwindow* window;
    int initializeGlfw();
    int createWindow();
    int initializeGlew();
    
};

#endif /* defined(__mem_game__setup__) */
