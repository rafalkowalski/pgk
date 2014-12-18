// Include standard headers
#include <stdio.h>
#include <stdlib.h>

// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>
#include "colors.h"
GLFWwindow* window;

// Include GLM
#include <glm/glm.hpp>
using namespace glm;
using namespace std;
#include <vector>
#include "shader.hpp"
#include "board.h"
#include "game.h"
#include "setup.h"
#include "colors.h"

#define PRESS_UP 0
#define PRESS_RIGHT 1
#define PRESS_DOWN 2
#define PRESS_LEFT 3

#define SHOW 1
#define HIDDEN 0
#define DISABLED 2

#define TRIANGLE 1
#define SQUARE 2
#define DIAMOND 3
#define TRAPEZE 4
#define PARALLELOGRAM 5
#define TRIAN_2 6
#define DIAMOND_2 7
#define DIAMOND_3 8

#include <unistd.h>
vector<GLfloat> g_vertex_buffer_data;

Board board;
int round_counter = 0;

void updated_position(int pressedKey){
    int current_position = board.get_current_position();
    int tempX = board.get_current_position() % 4;
    int tempY = board.get_current_position() / 4;
    
    if (pressedKey == PRESS_UP) {
        if (tempY > 0 )
            board.set_current_position(current_position-4);
        
    }
    if (pressedKey == PRESS_RIGHT) {
        if (tempX <3 )
            board.set_current_position(current_position+1);
        
    }
    if (pressedKey == PRESS_DOWN) {
        if (tempY < 3 )
            board.set_current_position(current_position+4);
        
    }
    if (pressedKey == PRESS_LEFT) {
        if (tempX >0 )
            board.set_current_position(current_position-1);
        
    }
    
    
}


void recolor_card(int current_index, Card &card){
    if (card.get_status() == HIDDEN){
        card.set_status(SHOW);
    }
}



void keyCalback(GLFWwindow* w, int key, int scancode, int action, int mods)
{
    
    if(key == GLFW_KEY_UP && action == GLFW_PRESS){
        updated_position(PRESS_UP);
    }
    if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
        updated_position(PRESS_RIGHT);
    }
    if(key == GLFW_KEY_LEFT && action == GLFW_PRESS){
        updated_position(PRESS_LEFT);
    }
    if(key == GLFW_KEY_DOWN && action == GLFW_PRESS){
        updated_position(PRESS_DOWN);
    }
    if(key == GLFW_KEY_ENTER && action == GLFW_PRESS){
        if (board.is_two_selected())
        {
            int first_id = board.first_card_id;
            int second_id = board.second_card_id;
            board.is_two_cards_equal(first_id,second_id);
            round_counter++;
            printf("Round: %d\n", round_counter);

        }
        
        int current_index = board.get_current_position();
        Card &card = board.get_current_board()[current_index];
        recolor_card(current_index, card);
        
    }
}

void draw_card(Card &card){
    
    float x1 = card.get_x1();
    float y1 = card.get_y1();
    float size = 0.4;
    g_vertex_buffer_data.push_back(x1);
    g_vertex_buffer_data.push_back(y1);
    
    g_vertex_buffer_data.push_back(x1+size);
    g_vertex_buffer_data.push_back(y1);
    
    g_vertex_buffer_data.push_back(x1);
    g_vertex_buffer_data.push_back(y1-size);
    
    g_vertex_buffer_data.push_back(x1+size);
    g_vertex_buffer_data.push_back(y1-size);
    
}

void draw_current_cursor(Card &cursor){
    float x1 = cursor.get_x1();
    float y1 = cursor.get_y1();
    float size = 0.5;
    g_vertex_buffer_data.push_back(x1);
    g_vertex_buffer_data.push_back(y1);
    
    g_vertex_buffer_data.push_back(x1+size);
    g_vertex_buffer_data.push_back(y1);
    
    g_vertex_buffer_data.push_back(x1+size);
    g_vertex_buffer_data.push_back(y1-size);
    
    g_vertex_buffer_data.push_back(x1);
    g_vertex_buffer_data.push_back(y1-size);
    
    g_vertex_buffer_data.push_back(x1);
    g_vertex_buffer_data.push_back(y1);
    
}

void draw_shape(Card &card){
    float x1 = card.get_x1();
    float y1 = card.get_y1();
    
    if (card.get_shape() == TRIANGLE){
        int i = (int)(g_vertex_buffer_data.size());
        float size = 0.20;
        card.set_place(i/2);
        g_vertex_buffer_data.push_back(x1+size);
        g_vertex_buffer_data.push_back(y1-0.10);
    
        g_vertex_buffer_data.push_back(x1+size+0.10);
        g_vertex_buffer_data.push_back(y1-0.40);
    
        g_vertex_buffer_data.push_back(x1+size-0.10);
        g_vertex_buffer_data.push_back(y1-0.40);
    } else if(card.get_shape() == SQUARE){
        int i = (int)(g_vertex_buffer_data.size());
       
        card.set_place(i/2);
        g_vertex_buffer_data.push_back(x1+0.05);
        g_vertex_buffer_data.push_back(y1-0.05);
        
        g_vertex_buffer_data.push_back(x1+0.35);
        g_vertex_buffer_data.push_back(y1-0.05);
        
        g_vertex_buffer_data.push_back(x1+0.05);
        g_vertex_buffer_data.push_back(y1-0.35);
        
        g_vertex_buffer_data.push_back(x1+0.35);
        g_vertex_buffer_data.push_back(y1-0.35);
    } else if (card.get_shape() == DIAMOND){
        int i = (int)(g_vertex_buffer_data.size());
        card.set_place(i/2);
        
        g_vertex_buffer_data.push_back(x1+0.20);
        g_vertex_buffer_data.push_back(y1-0.10);
        
        g_vertex_buffer_data.push_back(x1+0.30);
        g_vertex_buffer_data.push_back(y1-0.20);
        
        g_vertex_buffer_data.push_back(x1+0.20);
        g_vertex_buffer_data.push_back(y1-0.30);
        
        g_vertex_buffer_data.push_back(x1+0.10);
        g_vertex_buffer_data.push_back(y1-0.20);
    } else if(card.get_shape() == TRAPEZE){
        int i = (int)(g_vertex_buffer_data.size());
        
        card.set_place(i/2);
        g_vertex_buffer_data.push_back(x1+0.10);
        g_vertex_buffer_data.push_back(y1-0.05);
        
        g_vertex_buffer_data.push_back(x1+0.30);
        g_vertex_buffer_data.push_back(y1-0.05);
        
        g_vertex_buffer_data.push_back(x1+0.05);
        g_vertex_buffer_data.push_back(y1-0.35);
        
        g_vertex_buffer_data.push_back(x1+0.35);
        g_vertex_buffer_data.push_back(y1-0.35);
    }else if(card.get_shape() == PARALLELOGRAM){
        int i = (int)(g_vertex_buffer_data.size());
        
        card.set_place(i/2);
        g_vertex_buffer_data.push_back(x1+0.15);
        g_vertex_buffer_data.push_back(y1-0.05);
        
        g_vertex_buffer_data.push_back(x1+0.30);
        g_vertex_buffer_data.push_back(y1-0.05);
        
        g_vertex_buffer_data.push_back(x1+0.05);
        g_vertex_buffer_data.push_back(y1-0.35);
        
        g_vertex_buffer_data.push_back(x1+0.20);
        g_vertex_buffer_data.push_back(y1-0.35);
    }else if (card.get_shape() == TRIAN_2){
        int i = (int)(g_vertex_buffer_data.size());
        card.set_place(i/2);
        g_vertex_buffer_data.push_back(x1+0.10);
        g_vertex_buffer_data.push_back(y1-0.05);
        
        g_vertex_buffer_data.push_back(x1+0.25);
        g_vertex_buffer_data.push_back(y1-0.05);
        

        g_vertex_buffer_data.push_back(x1+0.05);
        g_vertex_buffer_data.push_back(y1-0.35);
        
        g_vertex_buffer_data.push_back(x1+0.25);
        g_vertex_buffer_data.push_back(y1-0.35);
    }else if (card.get_shape() == DIAMOND_2){
        int i = (int)(g_vertex_buffer_data.size());
        card.set_place(i/2);
        
        g_vertex_buffer_data.push_back(x1+0.20);
        g_vertex_buffer_data.push_back(y1-0.10);
        
        g_vertex_buffer_data.push_back(x1+0.30);
        g_vertex_buffer_data.push_back(y1-0.10);
        
        g_vertex_buffer_data.push_back(x1+0.30);
        g_vertex_buffer_data.push_back(y1-0.30);
        
        g_vertex_buffer_data.push_back(x1+0.10);
        g_vertex_buffer_data.push_back(y1-0.10);
    } else if (card.get_shape() == DIAMOND_3){
        int i = (int)(g_vertex_buffer_data.size());
        card.set_place(i/2);
        
        g_vertex_buffer_data.push_back(x1+0.0);
        g_vertex_buffer_data.push_back(y1-0.10);
        
        g_vertex_buffer_data.push_back(x1+0.30);
        g_vertex_buffer_data.push_back(y1-0.20);
        
        g_vertex_buffer_data.push_back(x1+0.20);
        g_vertex_buffer_data.push_back(y1-0.20);
        
        g_vertex_buffer_data.push_back(x1+0.10);
        g_vertex_buffer_data.push_back(y1-0.20);
    }
    
}


void draw_board(){
    vector<Card> current_board = board.get_current_board();
    for (int i = 0; i < current_board.size(); i++){
        if(i == 16){
            draw_current_cursor(current_board[i]);
        }else {
            draw_card(current_board[i]);
            
        }
    }
    
    for (int i = 0; i < current_board.size(); i++){
        Card &card = board.get_current_board()[i];
        
        draw_shape(card);
    }
}


int main( void )
{
    
    Setup setup;
    setup.init();
    window = setup.get_window();
    
    board.init_board();
    
    glfwSetKeyCallback(window, keyCalback);
    // Dark blue background
    glClearColor(0.0f, 0.0f, 0.4f, 0.0f);
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    
    
    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "SimpleVertexShader.vertexshader", "SimpleFragmentShader.fragmentshader" );
    
    GLuint ScaleID = glGetUniformLocation(programID, "scale");
    GLuint MoveXID = glGetUniformLocation(programID, "move_x");
    GLuint MoveYID = glGetUniformLocation(programID, "move_y");
    
    GLuint RedID = glGetUniformLocation(programID, "red");
    GLuint GreenID = glGetUniformLocation(programID, "green");
    GLuint BlueID = glGetUniformLocation(programID, "blue");
    
    draw_board();

    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(GLfloat)*g_vertex_buffer_data.size(), &g_vertex_buffer_data[0], GL_DYNAMIC_DRAW);
    
    /*glBindBuffer(GL_ARRAY_BUFFER, colorbuffer);
    glBufferData(GL_ARRAY_BUFFER, 2000, &g_color_buffer_data[0], GL_STATIC_DRAW);*/

    do{
        
        

        
        
        
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Use our shader
        glUseProgram(programID);
        
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
        
        
        // Draw the triangle !
        int k =0;
        for (int i = 0; i < 64; i+=4 ){
            Colors colors;
            Card card = board.get_current_board()[k];
            vector<float> color = colors.get_colors(card.get_color());
            
            
            glUniform1f(MoveXID,0.0);
            glUniform1f(MoveYID,0.0);
            if (card.get_status() == HIDDEN){
                glUniform1f(ScaleID,1.0);
                glUniform1f(RedID,0.0);
                glUniform1f(GreenID,0.0);
                glUniform1f(BlueID,0.0);
            } else if (card.get_status() == DISABLED){
                glUniform1f(ScaleID,1.0);
                glUniform1f(RedID,0.0);
                glUniform1f(GreenID,0.0);
                glUniform1f(BlueID,0.4);
            } else {
                glUniform1f(ScaleID,1.0);
                glUniform1f(RedID,color[0]);
                glUniform1f(GreenID, color[1]);
                glUniform1f(BlueID, color[2]);
            }
            k++;
            glDrawArrays(GL_TRIANGLE_STRIP, i, 4);
        }
        // Draw cursor
        
        int tempX = board.get_current_position() % 4;
        int tempY = board.get_current_position() / 4;
        
        glUniform1f(MoveXID, tempX * 0.5);
        glUniform1f(MoveYID, -tempY * 0.5);
        glUniform1f(RedID,1.0);
        glUniform1f(GreenID,1.0);
        glUniform1f(BlueID,0.4);
        glDrawArrays(GL_LINE_STRIP, 64, 5);
        
        for( int i =0 ; i< 16;i++){
            Card &card = board.get_current_board()[i];
            if (card.get_status() == SHOW){
                if (card.get_shape() == TRIANGLE){
                    glUniform1f(MoveXID,0.0);
                    glUniform1f(MoveYID,0.0);
                    glUniform1f(ScaleID,1.0);
                    glUniform1f(RedID,1.0);
                    glUniform1f(GreenID,1.0);
                    glUniform1f(BlueID,0.4);
                    glDrawArrays(GL_TRIANGLE_STRIP, card.get_place(), 3);
                } else if (card.get_shape() == SQUARE){
                    glUniform1f(MoveXID,0.0);
                    glUniform1f(MoveYID,0.0);
                    glUniform1f(ScaleID,1.0);
                    glUniform1f(RedID,1.0);
                    glUniform1f(GreenID,1.0);
                    glUniform1f(BlueID,0.4);
                    glDrawArrays(GL_TRIANGLE_STRIP, card.get_place(), 4);
                }
                else if (card.get_shape() == DIAMOND){
                    glUniform1f(MoveXID,0.0);
                    glUniform1f(MoveYID,0.0);
                    glUniform1f(ScaleID,1.0);
                    glUniform1f(RedID,0.0);
                    glUniform1f(GreenID,1.0);
                    glUniform1f(BlueID,0.4);
                    glDrawArrays(GL_TRIANGLE_STRIP, card.get_place(), 4);
                } else if (card.get_shape() == TRAPEZE){
                    glUniform1f(MoveXID,0.0);
                    glUniform1f(MoveYID,0.0);
                    glUniform1f(ScaleID,1.0);
                    glUniform1f(RedID,0.0);
                    glUniform1f(GreenID,1.0);
                    glUniform1f(BlueID,0.4);
                    glDrawArrays(GL_TRIANGLE_STRIP, card.get_place(), 4);
                }else if (card.get_shape() == PARALLELOGRAM){
                    glUniform1f(MoveXID,0.0);
                    glUniform1f(MoveYID,0.0);
                    glUniform1f(ScaleID,1.0);
                    glUniform1f(RedID,0.0);
                    glUniform1f(GreenID,0.5);
                    glUniform1f(BlueID,1.0);
                    glDrawArrays(GL_TRIANGLE_STRIP, card.get_place(), 4);
                }else if (card.get_shape() == TRIAN_2){
                    glUniform1f(MoveXID,0.0);
                    glUniform1f(MoveYID,0.0);
                    glUniform1f(ScaleID,1.0);
                    glUniform1f(RedID,1.0);
                    glUniform1f(GreenID,1.0);
                    glUniform1f(BlueID,0.4);
                    glDrawArrays(GL_TRIANGLE_STRIP, card.get_place(), 4);
                }else if (card.get_shape() == DIAMOND_2){
                    glUniform1f(MoveXID,0.0);
                    glUniform1f(MoveYID,0.0);
                    glUniform1f(ScaleID,1.0);
                    glUniform1f(RedID,0.0);
                    glUniform1f(GreenID,1.0);
                    glUniform1f(BlueID,0.4);
                    glDrawArrays(GL_TRIANGLE_STRIP, card.get_place(), 4);
                }else if (card.get_shape() == DIAMOND_3){
                    glUniform1f(MoveXID,0.0);
                    glUniform1f(MoveYID,0.0);
                    glUniform1f(ScaleID,1.0);
                    glUniform1f(RedID,0.0);
                    glUniform1f(GreenID,1.0);
                    glUniform1f(BlueID,0.4);
                    glDrawArrays(GL_TRIANGLE_STRIP, card.get_place(), 4);
                }
                
            }
        }
        
        glDisableVertexAttribArray(0);
        
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();
        
        
        
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    // Cleanup VBO
    glDeleteBuffers(1, &vertexbuffer);
    glDeleteVertexArrays(1, &VertexArrayID);
    glDeleteProgram(programID);
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}

