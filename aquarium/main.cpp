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

#include "colors.h"

#include <vector>
#include "OpenGl.h"

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtx/rotate_vector.hpp>
#include "Bubble.h"
#include "player.h"
#include "Aquarium.h"

#define STOP 6
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3
#define TOP 4
#define BOTTOM 5

#define PLAYER 1
#define AQUARIUM 0
bool can_move = true;
bool mode = true;


vector<GLfloat> g_vertex_buffer_data;
vector<glm::vec3> vertices;
vector<glm::vec3> normals;
glm::vec3 camera_pos(5,0,0); // look_at - glm::vec3(4,0,0);
glm::vec3 look_at(0,0,0); // player.get_pos()
glm::vec3 camera_up(0,1,0);
float camera_zoom= 45.0;

int LEVEL = 1;
Player player (-2.0,0.0,0.0);
Aquarium aquarium (2,1,1);
bool cam_pos_left = false;
bool cam_pos_right = false;
bool cam_pos_up = false;
bool cam_pos_down = false;
vector<Bubble> bubbles;

void keyCalback(GLFWwindow* w, int key, int scancode, int action, int mods){
    if(key == GLFW_KEY_RIGHT && action == GLFW_PRESS){
        cam_pos_right = true;
    }
    if(key == GLFW_KEY_RIGHT && action == GLFW_RELEASE){
        cam_pos_right = false;
    }
    if(key == GLFW_KEY_LEFT && action == GLFW_PRESS){
        cam_pos_left = true;
    }
    if(key == GLFW_KEY_LEFT && action == GLFW_RELEASE){
        cam_pos_left = false;
    }
    if(key == GLFW_KEY_UP && action == GLFW_PRESS){
        cam_pos_up = true;
    }
    if(key == GLFW_KEY_UP && action == GLFW_RELEASE){
        cam_pos_up = false;
    }
    if(key == GLFW_KEY_DOWN && action == GLFW_PRESS){
        cam_pos_down = true;
    }
    if(key == GLFW_KEY_DOWN && action == GLFW_RELEASE){
        cam_pos_down = false;
    }
    
    if(key == GLFW_KEY_9 && action == GLFW_PRESS){
        camera_zoom += 1.0;
    }
    if(key == GLFW_KEY_0 && action == GLFW_PRESS){
        camera_zoom -= 1.0;
    }
    
    if(key == GLFW_KEY_P&& action == GLFW_PRESS){
        
    }
    if(key == GLFW_KEY_W&& action == GLFW_PRESS){
        player.key = UP;
    }
    if(key == GLFW_KEY_W && action == GLFW_RELEASE){
        player.key = STOP;
    }
    if(key == GLFW_KEY_S&& action == GLFW_PRESS){
        player.key = DOWN;
    }
    if(key == GLFW_KEY_S && action == GLFW_RELEASE){
        player.key = STOP;
    }
    if(key == GLFW_KEY_A&& action == GLFW_PRESS){
        player.key = LEFT;
    }
    if(key == GLFW_KEY_A && action == GLFW_RELEASE){
        player.key = STOP;
    }
    if(key == GLFW_KEY_D&& action == GLFW_PRESS){
        player.key = RIGHT;
    }
    if(key == GLFW_KEY_D && action == GLFW_RELEASE){
        player.key = STOP;
    }
    if(key == GLFW_KEY_Z&& action == GLFW_PRESS){
        player.key = TOP;
    }
    if(key == GLFW_KEY_Z && action == GLFW_RELEASE){
        player.key = STOP;
    }
    if(key == GLFW_KEY_X&& action == GLFW_PRESS){
        player.key = BOTTOM;
    }
    if(key == GLFW_KEY_X && action == GLFW_RELEASE){
        player.key = STOP;
    }
    if(key == GLFW_KEY_TAB && action == GLFW_PRESS){
        mode = !mode;
        if(mode){
            look_at = player.get_position(); // player.get_pos()
            camera_pos = look_at - glm::vec3(3,0,0);
            
        }else{
            camera_pos = glm::vec3 (5,0,0);
            look_at = glm::vec3 (0,0,0);
        }
    }
    
    
}

void add_sphere_to_vector(float cx, float cy, float cz, float r, int p, vector<glm::vec3> &verticesa, vector<glm::vec3> &normalsa)
{
    float theta1 = 0.0, theta2 = 0.0, theta3 = 0.0;
    float ex = 0.0f, ey = 0.0f, ez = 0.0f;
    float px = 0.0f, py = 0.0f, pz = 0.0f;
    GLfloat vertices[p*6+6], normals[p*6+6], texCoords[p*4+4];
    
    if( r < 0 )
        r = -r;
    
    if( p < 0 )
        p = -p;
    
    for(int i = 0; i < p/2; ++i)
    {
        theta1 = i * (M_PI*2) / p - M_PI_2;
        theta2 = (i + 1) * (M_PI*2) / p - M_PI_2;
        
        for(int j = 0; j <= p; ++j)
        {
            theta3 = j * (M_PI*2) / p;
            
            ex = cosf(theta2) * cosf(theta3);
            ey = sinf(theta2);
            ez = cosf(theta2) * sinf(theta3);
            px = cx + r * ex;
            py = cy + r * ey;
            pz = cz + r * ez;
            
            vertices[(6*j)+(0%6)] = px;
            vertices[(6*j)+(1%6)] = py;
            vertices[(6*j)+(2%6)] = pz;
            verticesa.push_back(glm::vec3 (px,py,pz));
            
            normals[(6*j)+(0%6)] = ex;
            normals[(6*j)+(1%6)] = ey;
            normals[(6*j)+(2%6)] = ez;
            normalsa.push_back(glm::vec3 (ex,ey,ez));
            
            texCoords[(4*j)+(0%4)] = -(j/(float)p);
            texCoords[(4*j)+(1%4)] = 2*(i+1)/(float)p;
            
            
            ex = cosf(theta1) * cosf(theta3);
            ey = sinf(theta1);
            ez = cosf(theta1) * sinf(theta3);
            px = cx + r * ex;
            py = cy + r * ey;
            pz = cz + r * ez;
            
            vertices[(6*j)+(3%6)] = px;
            vertices[(6*j)+(4%6)] = py;
            vertices[(6*j)+(5%6)] = pz;
            
            verticesa.push_back(glm::vec3 (px,py,pz));
            normals[(6*j)+(3%6)] = ex;
            normals[(6*j)+(4%6)] = ey;
            normals[(6*j)+(5%6)] = ez;
            normalsa.push_back(glm::vec3 (ex,ey,ez));
            
            texCoords[(4*j)+(2%4)] = -(j/(float)p);
            texCoords[(4*j)+(3%4)] = 2*i/(float)p;
        }
    }
}


int add_cubic_to_vector(){
    int index_start = vertices.size();
    
    // Top face (y = 1.0f)
    vertices.push_back(glm::vec3 ( 1.0f, 1.0f,  1.0f));
    vertices.push_back(glm::vec3 (-1.0f, 1.0f,  1.0f));
    vertices.push_back(glm::vec3 (-1.0f, 1.0f, -1.0f));
    vertices.push_back(glm::vec3 ( 1.0f, 1.0f, -1.0f));
    normals.push_back(glm::vec3 (0,-1,0));
    normals.push_back(glm::vec3 (0,-1,0));
    normals.push_back(glm::vec3 (0,-1,0));
    normals.push_back(glm::vec3 (0,-1,0));
    
    // Bottom face (y = -1.0f)
    
    vertices.push_back(glm::vec3 ( 1.0f, -1.0f, -1.0f));
    vertices.push_back(glm::vec3 (-1.0f, -1.0f, -1.0f));
    vertices.push_back(glm::vec3 (-1.0f, -1.0f,  1.0f));
    vertices.push_back(glm::vec3 ( 1.0f, -1.0f,  1.0f));
    normals.push_back(glm::vec3 (0,1,0));
    normals.push_back(glm::vec3 (0,1,0));
    normals.push_back(glm::vec3 (0,1,0));
    normals.push_back(glm::vec3 (0,1,0));
    
    // Front face  (z = 1.0f)
    vertices.push_back(glm::vec3 ( 1.0f, -1.0f, 1.0f));
    vertices.push_back(glm::vec3 (-1.0f, -1.0f, 1.0f));
    vertices.push_back(glm::vec3 (-1.0f,  1.0f, 1.0f));
    vertices.push_back(glm::vec3 ( 1.0f,  1.0f, 1.0f));
    normals.push_back(glm::vec3 (0,0,1));
    normals.push_back(glm::vec3 (0,0,1));
    normals.push_back(glm::vec3 (0,0,1));
    normals.push_back(glm::vec3 (0,0,1));
    
    // Back face (z = -1.0f)
    
    
    vertices.push_back(glm::vec3 ( 1.0f,  1.0f, -1.0f));
    vertices.push_back(glm::vec3 (-1.0f,  1.0f, -1.0f));
    vertices.push_back(glm::vec3 (-1.0f, -1.0f, -1.0f));
    vertices.push_back(glm::vec3 ( 1.0f, -1.0f, -1.0f));
    normals.push_back(glm::vec3 (0,0,-1));
    normals.push_back(glm::vec3 (0,0,-1));
    normals.push_back(glm::vec3 (0,0,-1));
    normals.push_back(glm::vec3 (0,0,-1));
    
    // Left face (x = -1.0f)
    
    vertices.push_back(glm::vec3 (-1.0f, -1.0f,  1.0f));
    vertices.push_back(glm::vec3 (-1.0f, -1.0f, -1.0f));
    vertices.push_back(glm::vec3 (-1.0f,  1.0f, -1.0f));
    vertices.push_back(glm::vec3 (-1.0f,  1.0f,  1.0f));
    normals.push_back(glm::vec3 (-1,0,0));
    normals.push_back(glm::vec3 (-1,0,0));
    normals.push_back(glm::vec3 (-1,0,0));
    normals.push_back(glm::vec3 (-1,0,0));
    
    // Right face (x = 1.0f)
    
    vertices.push_back(glm::vec3 (1.0f, -1.0f, -1.0f));
    vertices.push_back(glm::vec3 (1.0f, -1.0f,  1.0f));
    vertices.push_back(glm::vec3 (1.0f,  1.0f,  1.0f));
    vertices.push_back(glm::vec3 (1.0f,  1.0f, -1.0f));
    normals.push_back(glm::vec3 (1,0,0));
    normals.push_back(glm::vec3 (1,0,0));
    normals.push_back(glm::vec3 (1,0,0));
    normals.push_back(glm::vec3 (1,0,0));
    return index_start;
}

void render_cubic(){
    for(int i = 0; i <= 24; i+=4){
        glDrawArrays(GL_TRIANGLE_FAN, i, 4 );
        
    }
}

void test_cubic_collision(Bubble &bubble){
    int top = 1;
    
    if(top < (bubble.get_y()+bubble.get_radius())){
        bubble.reset();
    }
}

void generate_bubble(){
    for(int i =0 ; i < 100; i++){
        float z = (-5 + ( std::rand() % ( 10 + 1 ) ))*0.1;
        float x = (-10 + ( std::rand() % ( 20 + 1 ) ))*0.1;
        Bubble bubble (x,-1,z);
        bubbles.push_back(bubble);
    }
}

bool is_end(){
    if( player.get_x()+ player.get_radius() >= 2.0){
        LEVEL++;
        return true;
        // init new platform
    }
    return false;
}

void stop_all(){
    for(int i =0 ; i < bubbles.size(); i++){
        bubbles[i].stop();
    }
    can_move = false;
    
}

int main( void )
{
    srand( static_cast<unsigned>(time( NULL ) ) );
    Setup setup;
    
    setup.init();
    window = setup.get_window();
    add_cubic_to_vector();
    
    unsigned long sphere_start = vertices.size() + 1;
    add_sphere_to_vector(0.f, 0.f, 0.f, 1.f, 100,  vertices,  normals);
    unsigned long sphere_len = vertices.size() - sphere_start + 1;
    
    generate_bubble();
    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    // Dark blue background
    glClearColor(0.0f, 0.2f, 0.1f, 0.0f);
    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LESS);
    glEnable(GL_CULL_FACE);
    glfwSetKeyCallback(window, keyCalback);
    
    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);
    
    // Create and compile our GLSL program from the shaders
    GLuint programID = LoadShaders( "StandardShading.vertexshader", "StandardShading.fragmentshader" );
    
    // Get a handle for our "MVP" uniform
    GLuint MatrixID = glGetUniformLocation(programID, "MVP");
    GLuint ViewMatrixID = glGetUniformLocation(programID, "V");
    GLuint ModelMatrixID = glGetUniformLocation(programID, "M");
    GLuint ColorID = glGetUniformLocation(programID, "vecColor");
    
    
    // Load it into a VBO
    
    GLuint vertexbuffer;
    glGenBuffers(1, &vertexbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);
    
    GLuint normalbuffer;
    glGenBuffers(1, &normalbuffer);
    glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
    glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);
    
    // Get a handle for our "LightPosition" uniform
    glUseProgram(programID);
    GLuint LightID = glGetUniformLocation(programID, "LightPosition_worldspace");
    
    GLuint PositionID = glGetUniformLocation(programID, "Position_worldspace");
    
    do{
        
        glClear(GL_COLOR_BUFFER_BIT);
        if (cam_pos_left){
            glm::vec3  temp = camera_pos - look_at;
            temp = glm::rotateY(temp, -2.f);
            camera_pos = temp + look_at;
        }
        if(cam_pos_right){
            glm::vec3  temp = camera_pos - look_at;
            temp = glm::rotateY(temp, 2.f);
            camera_pos = temp + look_at;
        }
        if(cam_pos_up){
            
            glm::vec3 tempVec = camera_pos - look_at;
            glm::vec3 crossProd = glm::cross(glm::normalize(tempVec), camera_up);
            
            tempVec = glm::rotate(tempVec, -static_cast<float>(-2.f), crossProd);
            float angle = glm::angle(glm::normalize(tempVec), camera_up);
            if (angle > 10.f)
            {
                camera_pos = look_at + tempVec;
            }
        }
        if(cam_pos_down){
            
            glm::vec3 tempVec = camera_pos - look_at;
            glm::vec3 crossProd = glm::cross(glm::normalize(tempVec), camera_up);
            
            tempVec = glm::rotate(tempVec, -static_cast<float>(2.f), crossProd);
            float angle = glm::angle(glm::normalize(tempVec), camera_up);
            if (angle < 170.f)
            {
                camera_pos = look_at + tempVec;
            }
        }
       
        
        if(can_move){
            player.update();
            if(mode){
                glm::vec3 temp = camera_pos - look_at;
                look_at = player.get_position(); // player.get_pos()
                camera_pos = temp + look_at;
            }
        }
        if(is_end()){
            player.reset();
        }
        
       
        
        for(int i = 0; i < bubbles.size()  ; i++){
            test_cubic_collision(bubbles[i]);
            if(bubbles[i].active){
                if(player.check_collision(bubbles[i])){
                    stop_all();
                }else{
                    bubbles[i].update();
                }
            }
        }
        // Use our shader
        glUseProgram(programID);
        // Draw nothing, see you in tutorial 2 !
        
        
        glm::vec3 lightPos = glm::vec3(4,4,4);
        glUniform3f(LightID, lightPos.x, lightPos.y, lightPos.z);
        
        // 1rst attribute buffer : vertices
        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
        glVertexAttribPointer(
                              0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
                              3,                  // size
                              GL_FLOAT,           // type
                              GL_FALSE,           // normalized?
                              0,                  // stride
                              (void*)0            // array buffer offset
                              );
        
        // 3rd attribute buffer : normals
        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
        glVertexAttribPointer(
                              1,    // The attribute we want to configure
                              3,                            // size
                              GL_FLOAT,                     // type
                              GL_FALSE,                     // normalized?
                              0,                            // stride
                              (void*)0                      // array buffer offset
                              );
        
        
        glm::mat4 ProjectionMatrix = glm::perspective(camera_zoom, 4.0f / 3.0f, 0.1f, 100.0f);
        
        glm::mat4 ViewMatrix = glm::lookAt(
                                           camera_pos, // Camera is at (4,3,3), in World Space
                                           look_at, // and looks at the origin
                                           camera_up // Head is up (set to 0,-1,0 to look upside-down)
                                           );
        
        glm::mat4 ModelMatrix;// = glm::scale(2.f, 1.f, 1.f);
        glm::mat4 MVP;// = ProjectionMatrix * ViewMatrix * ModelMatrix;
        
        // Send our transformation to the currently bound shader,
        // in the "MVP" uniform
        ModelMatrix = glm::scale(aquarium.get_length(), aquarium.get_width(), aquarium.get_height());
        MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
        glUniform3f(ColorID, 0 ,0, 1.0);
        render_cubic();
        
        glm::vec3 tempScale;
        tempScale = glm::vec3(player.get_radius(), player.get_radius(), player.get_radius());
        ModelMatrix = glm::translate(player.get_x(), player.get_y(), player.get_z()) * glm::scale(tempScale);
        MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
        glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
        glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
        glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
        glUniform3f(ColorID, 1.0, 0, 0);
        glDrawArrays(GL_TRIANGLE_STRIP, sphere_start, sphere_len);
        
        for(int i = 0; i < LEVEL  ; i++){
            bubbles[i].active = true;
            tempScale = glm::vec3(bubbles[i].get_radius(), bubbles[i].get_radius(), bubbles[i].get_radius());
            ModelMatrix = glm::translate(bubbles[i].get_x(), bubbles[i].get_y(), bubbles[i].get_z()) * glm::scale(tempScale);
            MVP = ProjectionMatrix * ViewMatrix * ModelMatrix;
            glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);
            glUniformMatrix4fv(ModelMatrixID, 1, GL_FALSE, &ModelMatrix[0][0]);
            glUniformMatrix4fv(ViewMatrixID, 1, GL_FALSE, &ViewMatrix[0][0]);
            glUniform3f(ColorID, 0, 1.0, 0);
            glDrawArrays(GL_TRIANGLE_STRIP, sphere_start, sphere_len);
        }
        
        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glfwSwapBuffers(window);
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        
    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
          glfwWindowShouldClose(window) == 0 );
    
    // Close OpenGL window and terminate GLFW
    glfwTerminate();
    
    return 0;
}

