//
//  board.h
//  mem-game
//
//  Created by Rafał on 21.10.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#ifndef __mem_game__board__
#define __mem_game__board__

#include <stdio.h>



// Include GLEW
#include <GL/glew.h>

// Include GLFW
#include <glfw3.h>

// Include GLM
#include <glm/glm.hpp>
using namespace glm;
using namespace std;
#include <vector>
#include "Card.h"



class Board
{
public:
    int first_card_id;
    int second_card_id;
    
    void init_board();
    vector<Card> &get_current_board(){return current_board; };
    void add_card_to_current_board(Card &card){ current_board.push_back(card); };
    void set_current_position(int p){ current_position = p ;};
    int get_current_position(){return current_position ;};
    
    bool is_two_cards_equal(int first_card_id, int second_card_id);
    
    void set_current_card_status(int status);
    bool is_two_selected();
    
private:
    int current_position;
    vector<Card> current_board;
};

#endif /* defined(__mem_game__board__) */
