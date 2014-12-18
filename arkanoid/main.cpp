#include <stdio.h>
#include <stdlib.h>

#include <GL/glew.h>

#include <glfw3.h>
GLFWwindow* window;

#include <glm/glm.hpp>
using namespace glm;
using namespace std;
#include "setup.h"
#include "shader.hpp"
#include "ball.h"
#include "Paddle.h"
#include "colors.h"
#include "Brick.h"
#include <vector>
#include "OpenGl.h"
#include "Collision.h"

vector<float> hexagon;
vector<GLfloat> g_vertex_buffer_data;
const float ball_velocity = 0.007;
const float paddle_size_x = 0.2;
const float paddle_size_y = 0.1;

Paddle paddle(0.0, -0.5, 0.2, 0.1, 0.01 );
Ball ball(0.0, 0.0, 0.01 , ball_velocity);
Collision collision(ball_velocity);

constexpr float blockWidth =0.15, blockHeight= 0.05;
constexpr int countBlocksX = 9, countBlocksY=4;


void keyCalback(GLFWwindow* w, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
        paddle.moveRight = true;
    }
    if(key == GLFW_KEY_RIGHT && action == GLFW_RELEASE){
        paddle.moveRight = false;
    }
    if(key == GLFW_KEY_LEFT && action == GLFW_PRESS){
        paddle.moveLeft = true;
    }
    if(key == GLFW_KEY_LEFT && action == GLFW_RELEASE){
        paddle.moveLeft = false;
    }
}

void draw_ball(){
    for(int i =1; i <364; i++){
        g_vertex_buffer_data.push_back((float) (0.01 * cos((3.14/180) * (float)i )));
        g_vertex_buffer_data.push_back((float) (0.01 * sin((3.14/180) * (float)i )));
    }
}

void draw_paddle(float x1, float y1,float size_x, float size_y){
    g_vertex_buffer_data.push_back(x1);
    g_vertex_buffer_data.push_back(y1);
    
    g_vertex_buffer_data.push_back(x1+size_x);
    g_vertex_buffer_data.push_back(y1);
    
    g_vertex_buffer_data.push_back(x1);
    g_vertex_buffer_data.push_back(y1-size_y);
    
    g_vertex_buffer_data.push_back(x1+size_x);
    g_vertex_buffer_data.push_back(y1-size_y);
}

void init_hexagon(){
    hexagon.push_back(-0.75);
    hexagon.push_back(1.0);
    hexagon.push_back(0.75);
    hexagon.push_back(1.0);
    hexagon.push_back(0.0);
    hexagon.push_back(0.0);
    
    hexagon.push_back(0.75);
    hexagon.push_back(1.0);
    hexagon.push_back(1.0);
    hexagon.push_back(0.0);
    hexagon.push_back(0.0);
    hexagon.push_back(0.0);
    
    hexagon.push_back(1.0);
    hexagon.push_back(0.0);
    hexagon.push_back(0.75);
    hexagon.push_back(-1.0);
    hexagon.push_back(0.0);
    hexagon.push_back(0.0);
    
    hexagon.push_back(0.75);
    hexagon.push_back(-1.0);
    hexagon.push_back(-0.75);
    hexagon.push_back(-1.0);
    hexagon.push_back(0.0);
    hexagon.push_back(0.0);
    
    hexagon.push_back(-1.0);
    hexagon.push_back(0.0);
    hexagon.push_back(-0.75);
    hexagon.push_back(-1.0);
    hexagon.push_back(0.0);
    hexagon.push_back(0.0);
    
    hexagon.push_back(-0.75);
    hexagon.push_back(1.0);
    hexagon.push_back(-1.0);
    hexagon.push_back(0.0);
    hexagon.push_back(0.0);
    hexagon.push_back(0.0);
    
}

unsigned g_hexagonOffset = 0;
void draw_hexagon(){
    g_hexagonOffset = static_cast<unsigned>(g_vertex_buffer_data.size()/2);
    for(int i =0; i < hexagon.size(); i++) {
        g_vertex_buffer_data.push_back(hexagon[i]);
    }
}

bool is_intersecting(Brick &brick, Ball &ball){
    return 	brick.right() >= ball.left() &&
    brick.left() <= ball.right() &&
    brick.bottom() >= ball.top() &&
    brick.top() <= ball.bottom();
}

void test_collision(Brick &brick, Ball &ball)
{
    if(brick.destroyed)
        return;
    
    if(!collision.is_intersecting(brick, ball)) return;
    
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

void draw_bricks(vector<Brick> bricks){
    for (int i =0 ; i < bricks.size(); i++){
        draw_paddle(bricks[i].get_x()-blockWidth/2, bricks[i].get_y()+blockHeight/2,blockWidth, blockHeight);
    }
}

vector<Brick>  get_bricks(){
    vector<Brick> bricks;
    for(int x=0; x < countBlocksX; ++x){
        for(int y=0; y < countBlocksY; ++y){
            int color = rand() % 9;
            bricks.emplace_back(-0.65 + (x + 0.01) * (blockWidth + 0.01) + 0.01,
                                0.55+(y + 0.02) * (blockHeight + 0.01),
                                blockWidth,
                                blockHeight,
                                color);
        }
    }
    return bricks;
}

int main( void )
{
    
    Setup setup;
    
    setup.init();
    window = setup.get_window();
    
    draw_paddle(paddle.get_x()-paddle_size_x/2,
                paddle.get_y()+paddle_size_y/2,
                paddle_size_x,
                paddle_size_y);
    
    draw_ball();
    
    
    vector<Brick> bricks = get_bricks();
    draw_bricks(bricks);
    
    init_hexagon();
    draw_hexagon();
    
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    glfwSetKeyCallback(window, keyCalback);
    
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
    
    OpenGl opengl(programID);
    
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*g_vertex_buffer_data.size(), &g_vertex_buffer_data[0], GL_DYNAMIC_DRAW);
    
    do{
        glClear(GL_COLOR_BUFFER_BIT);
        if(ball.get_y() < -1.0){
            ball.set_y(0.0);
            
        }
        // Use our shader
        glUseProgram(programID);
        // Draw nothing, see you in tutorial 2 !
        
        
        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                              0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                              2,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );
        
        opengl.draw_hexagon(g_hexagonOffset);
        ball.update();
        paddle.update(666);
        
        collision.test_collision(paddle, ball, ball_velocity);
        
        
        for(auto& brick : bricks) test_collision(brick, ball);
        
        // Ball
        opengl.draw_ball(ball.get_x(), ball.get_y());
        
        // Paddle
        opengl.draw_paddle(paddle.get_x());
        
        opengl.draw_bricks(bricks);
        
        
        
        // Swap buffers
        glDisableVertexAttribArray(0);
        glfwSwapBuffers(window);
        glfwPollEvents();
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}

