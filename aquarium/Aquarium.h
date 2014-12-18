//
//  Aquarium.h
//  mem-game
//
//  Created by Rafał on 14.12.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#ifndef __mem_game__Aquarium__
#define __mem_game__Aquarium__

#include <stdio.h>
#include <glm/glm.hpp>
class Aquarium
{
    
public:
    Aquarium(float length, float width, float heigth);
    float get_x(){return position.x;}
    float get_y(){return position.y;}
    float get_z(){return position.z;}
    
    float get_length(){return size.x;}
    float get_height(){return size.y;}
    float get_width(){return size.z;}
private:
    glm::vec3 position, size;
};

#endif /* defined(__mem_game__Aquarium__) */
