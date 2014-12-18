//
//  Aquarium.cpp
//  mem-game
//
//  Created by Rafał on 14.12.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#include "Aquarium.h"

Aquarium::Aquarium(float length, float width, float height){
    
    position.x = 0.0;
    position.y = 0.0;
    position.z = 0.0;
    size.x = length;
    size.y = height;
    size.z = width;
}