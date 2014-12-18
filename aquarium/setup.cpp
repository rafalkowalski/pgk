//
//  setup.cpp
//  mem-game
//
//  Created by Rafał on 24.10.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#include "setup.h"
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

void Setup::init(){
    initializeGlfw();
    createWindow();
    initializeGlew();
    
}

GLFWwindow* Setup::get_window(){
    return window;
}

int Setup::initializeGlfw(){
    // Initialise GLFW
    if( !glfwInit() )
    {
        fprintf( stderr, "Failed to initialize GLFW\n" );
        return -1;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // <--- to dodalem
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    
   
    return 0;
}

int Setup::initializeGlew(){
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile
    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        return -1;
    }
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    return 0;
}

int Setup::createWindow(){
    // Open a window and create its OpenGL context
    window = glfwCreateWindow( 1024, 768, "Akwarium", NULL, NULL);
    if( window == NULL ){
        fprintf( stderr, "Failed to open GLFW window. If you have an Intel GPU, they are not 3.3 compatible. Try the 2.1 version of the tutorials.\n" );
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    return 0;
}