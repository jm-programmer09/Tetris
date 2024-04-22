#pragma once

#include<SDL.h>
#include "source.cpp"
#include "tetris.h"

// The player class
// the plan is to have the player identified in a matrix[3][3]


// To prevent reinitialisation
#ifndef Player_Init
#define Player_Init

class Player {
public:
    int x; // Cords of the Game grid
    int y;
    Colour colour;
    Block block;
    BlockMapT player_map; // player grid map
    int current_rotation;

    Player(int x, int y) :
        x(x), y(y)
    {
        // this - first two are for intialising things not in the parameters
        colour = static_cast<Colour>(generateRandNum(3));
        block = static_cast<Block>(generateRandNum(7));

        // For setting the colour
        switch (block) {
        case Block::Single:
            colour = Colour::Yellow;
            break;
        case Block::LongUp:
            colour = Colour::Cyan;
            break;
        case Block::L:
            colour = Colour::Orange;
            break;
        case Block::ReverseL:
            colour = Colour::Blue;
            break;
        case Block::T:
            colour = Colour::Purple;
            break;
        case Block::S:
            colour = Colour::Green;
            break;
        case Block::Z:
            colour = Colour::Red;
            break;
        }

        current_rotation = 0;
        player_map = BlockMap.at(block)[current_rotation];
    }
};

#endif