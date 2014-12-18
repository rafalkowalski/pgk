//
//  board.cpp
//  mem-game
//
//  Created by Rafał on 21.10.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#include "board.h"
// Include standard headers
#include <stdio.h>

// Include GLFW
#include <glfw3.h>

using namespace std;
#include <vector>
#define SHOW 1
#define HIDDEN 0
#define DISABLED 2

#define BLACK 0
#define WHITE 1
#define RED 2
#define YELLOW 3
#define GREEN 4
#define BLUE 5
#define BROWN 6
#define PINK 7
#define GREY 8

#define SQUARE 2
#define TRIAN 1
#define DIAMOND 3
#define TRAPEZE 4
#define PARALLELOGRAM 5
#define TRIAN_2 6
#define DIAMOND_2 7
#define DIAMOND_3 8

#include <iostream>     // std::cout
#include <algorithm>    // std::shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>
using namespace std;

void Board::init_board(){
    Card card1,card2,card3,card4,card5,card6,card7,card8,card9,card10,card11,card12,card13,card14,card15,card16;
    
    
    vector<int> numbers;
    array<int,8> foo  {1,2,3,4,5,6,7,8};
    
    // obtain a time-based seed:
    unsigned seed = chrono::system_clock::now().time_since_epoch().count();
    
    shuffle (foo.begin(), foo.end(), std::default_random_engine(seed));
    
    
    
    card1.set_x1(-0.95);
    card1.set_y1(0.95);
    card1.set_color(RED);
    card1.set_shape(TRIAN);
    
    card2.set_x1(-0.45);
    card2.set_y1(0.95);
    card2.set_color(WHITE);
    card2.set_shape(SQUARE);
    
    card3.set_x1(0.05);
    card3.set_y1(0.95);
    card3.set_color(YELLOW);
    card3.set_shape(DIAMOND);
    
    card4.set_x1(0.55);
    card4.set_y1(0.95);
    card4.set_color(BLUE);
    card4.set_shape(TRAPEZE);
    
    
    card5.set_x1(-0.95);
    card5.set_y1(0.45);
    card5.set_color(BLUE);
    card5.set_shape(TRAPEZE);
    
    card6.set_x1(-0.45);
    card6.set_y1(0.45);
    card6.set_color(GREEN);
    card6.set_shape(PARALLELOGRAM);
    
    card7.set_x1(0.05);
    card7.set_y1(0.45);
    card7.set_color(RED);
    card7.set_shape(TRIAN);
    
    card8.set_x1(0.55);
    card8.set_y1(0.45);
    card8.set_color(BROWN);
    card8.set_shape(TRIAN_2);
    
    card9.set_x1(-0.95);
    card9.set_y1(-0.05);
    card9.set_color(WHITE);
    card9.set_shape(SQUARE);
    
    card10.set_x1(-0.45);
    card10.set_y1(-0.05);
    card10.set_color(BROWN);
    card10.set_shape(TRIAN_2);
    
    card11.set_x1(0.05);
    card11.set_y1(-0.05);
    card11.set_color(GREY);
    card11.set_shape(DIAMOND_2);
    
    card12.set_x1(0.55);
    card12.set_y1(-0.05);
    card12.set_color(PINK);
    card12.set_shape(DIAMOND_3);
    
    card13.set_x1(-0.95);
    card13.set_y1(-0.55);
    card13.set_color(GREY);
    card13.set_shape(DIAMOND_2);
    
    card14.set_x1(-0.45);
    card14.set_y1(-0.55);
    card14.set_color(PINK);
    card14.set_shape(DIAMOND_3);
    
    card15.set_x1(0.05);
    card15.set_y1(-0.55);
    card15.set_color(GREEN);
    card15.set_shape(PARALLELOGRAM);
    
    card16.set_x1(0.55);
    card16.set_y1(-0.55);
    card16.set_color(YELLOW);
    card16.set_shape(DIAMOND);
    
//    card1.set_color(foo[0]);
//    card2.set_color(foo[1]);
//    card3.set_color(foo[2]);
//    card4.set_color(foo[3]);
//    card5.set_color(foo[4]);
//    card6.set_color(foo[5]);
//    card7.set_color(foo[6]);
//    card8.set_color(foo[7]);
//    card9.set_color(foo[0]);
//    card10.set_color(foo[1]);
//    card12.set_color(foo[2]);
//    card11.set_color(foo[3]);
//    card13.set_color(foo[4]);
//    card14.set_color(foo[5]);
//    card15.set_color(foo[6]);
//    card16.set_color(foo[7]);
  
    
    add_card_to_current_board(card1);
    add_card_to_current_board(card2);
    add_card_to_current_board(card3);
    add_card_to_current_board(card4);
    
    add_card_to_current_board(card5);
    add_card_to_current_board(card6);
    add_card_to_current_board(card7);
    add_card_to_current_board(card8);
    
    add_card_to_current_board(card9);
    add_card_to_current_board(card10);
    add_card_to_current_board(card11);
    add_card_to_current_board(card12);
    
    add_card_to_current_board(card13);
    add_card_to_current_board(card14);
    add_card_to_current_board(card15);
    add_card_to_current_board(card16);
    
    
    
    Card coursor_card;
    coursor_card.set_x1(-1.0);
    coursor_card.set_y1(1.0);
    
    add_card_to_current_board(coursor_card);
    
    this->set_current_position(0);    
}



bool Board::is_two_cards_equal(int first_card_id, int second_card_id){
    Card &first_card = current_board[first_card_id];
    Card &second_card = current_board[second_card_id];
    if (first_card.get_color() == second_card.get_color()){
        first_card.set_status(DISABLED);
        second_card.set_status(DISABLED);
        return true;
    }
    first_card.set_status(HIDDEN);
    second_card.set_status(HIDDEN);
    return false;
}

bool Board::is_two_selected(){
    int sum = 0;
    int i = 0;
    for(;i < current_board.size();i++){
        if (current_board[i].get_status() == SHOW){
            sum += 1;
            if (sum == 1){
                first_card_id = i;
            }
            if (sum == 2){
                second_card_id = i;
                return true;
            }
        }
    }
    
    
    
    return false;
}

