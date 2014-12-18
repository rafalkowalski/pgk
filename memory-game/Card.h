//
//  Card.h
//  mem-game
//
//  Created by Rafał on 23.10.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#ifndef __mem_game__Card__
#define __mem_game__Card__

#include <stdio.h>

class Card
{
public:
    Card();
    Card(const Card& card);
    void set_status(int s) { status = s; }
    int get_status() { return status; }
    
    void set_color(int c) {color = c;};
    int get_color(){return color;};
    
    void set_x1(float p) { x1 = p; }
    void set_y1(float p) { y1 = p; }
    
    float get_x1(){return this->x1;};
    float get_y1(){return this->y1;};
    
    void set_shape(int sh) { shape = sh; }
    int get_shape() { return shape; }
    void set_place(int p) {place = p; }
    int get_place(){ return place;}
    
    
private:
    float x1, y1;
    int status;
    int color;
    int shape;
    int place;
    
};

#endif /* defined(__mem_game__Card__) */
