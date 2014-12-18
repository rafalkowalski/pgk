//
//  Card.cpp
//  mem-game
//
//  Created by Rafał on 23.10.2014.
//  Copyright (c) 2014 Rafał. All rights reserved.
//

#include "Card.h"

Card::Card(const Card& card)
{
    color = card.color;
    status = card.status;
    x1 = card.x1;
    y1 =card.y1;
    shape = card.shape;
    place = card.place;
    
}

Card::Card(){
    color = 0;
    status = 0;
    shape = 0;
    place = 0;
}