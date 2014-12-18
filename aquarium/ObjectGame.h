//
//  ObjectGame.h
//  mem-game
//
//  Created by Rafał on 22.11.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#ifndef __mem_game__ObjectGame__
#define __mem_game__ObjectGame__

#include <stdio.h>
#include <glm/glm.hpp>

class ObjectGame{
public:
    ObjectGame(glm::vec3 p){ position = p; };
    virtual glm::vec3  get_postion(){ return position; }
    virtual void  set_postion(glm::vec3 p){ position = p; }
protected:
    glm::vec3 position;
};

#endif /* defined(__mem_game__ObjectGame__) */
