//
//  colors.cpp
//  mem-game
//
//  Created by Rafał on 24.10.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#include "colors.h"

#define BLACK 0
#define WHITE 1
#define RED 2
#define YELLOW 3
#define GREEN 4
#define BLUE 5
#define BROWN 6
#define PINK 7
#define GREY 8
#define DISABLED 9

vector<float> Colors::get_colors(int color){
    if (color == BLACK)
        return black();
    if (color == WHITE)
        return white();
    if (color == RED)
        return red();
    if (color == YELLOW)
        return yellow();
    if (color == GREEN)
        return green();
    if (color == BLUE)
        return blue();
    if (color == BROWN)
        return brown();
    if (color == PINK)
        return pink();
    if (color == GREY)
        return grey();
    if (color == DISABLED)
        return disabled();
    return black();
}

vector<float> Colors::black(){
    vector<float> black;
    black.push_back(0);
    black.push_back(0);
    black.push_back(0);
    return black;
}
vector<float> Colors::white(){
    vector<float> white;
    white.push_back(1);
    white.push_back(1);
    white.push_back(1);
    return white;
}
vector<float> Colors::red(){
    vector<float> red;
    red.push_back(1);
    red.push_back(0);
    red.push_back(0);
    return red;
}

vector<float> Colors::yellow(){
    vector<float> yellow;
    yellow.push_back(1);
    yellow.push_back(1);
    yellow.push_back(0);
    return yellow;
}
vector<float> Colors::green(){
    vector<float> green;
    green.push_back(0);
    green.push_back(1);
    green.push_back(0);
    return green;
}
vector<float> Colors::blue(){
    vector<float> blue;
    blue.push_back(0);
    blue.push_back(0);
    blue.push_back(1);
    return blue;
}
vector<float> Colors::brown(){
    vector<float> brown;
    brown.push_back(0.35);
    brown.push_back(0.16);
    brown.push_back(0.14);
    return brown;
}
vector<float> Colors::pink(){
    vector<float> pink;
    pink.push_back(0.73);
    pink.push_back(0.56);
    pink.push_back(0.56);
    return pink;
}
vector<float> Colors::grey(){
    vector<float> grey;
    grey.push_back(0.4);
    grey.push_back(0.4);
    grey.push_back(0.4);
    return grey;
}

vector<float> Colors::disabled(){
    vector<float> disabled;
    disabled.push_back(0.0);
    disabled.push_back(0.0);
    disabled.push_back(0.4);
    return disabled;
}