//
//  colors.h
//  mem-game
//
//  Created by Rafał on 24.10.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//
#include <vector>
using namespace std;
#ifndef __mem_game__colors__
#define __mem_game__colors__

#include <stdio.h>
class Colors {
public:
vector<float>  get_colors(int color);
private :
vector<float> black();
vector<float> white();
vector<float> red();
vector<float> yellow();
vector<float> green();
vector<float> blue();
vector<float> brown();
vector<float> pink();
vector<float> grey();
vector<float> disabled();
};

#endif /* defined(__mem_game__colors__) */
