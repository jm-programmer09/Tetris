#pragma once

#include <array>
#include <iostream>
#include <string>
#include <stdexcept>



// For the Tetris Map
#ifndef TETRIS
#define TETRIS

// DEFINING
#define TETRIS_ROW_GRIDS 15
#define TETRIS_COLUMN_GRIDS 30 
#define TETRIS_CENTER 7
// For the width and the height of the area
#define GRID_SIZE 15
// Window Sizing
#define WINDOW_HEIGHT (GRID_SIZE * TETRIS_COLUMN_GRIDS) 
#define WINDOW_WIDTH (GRID_SIZE * TETRIS_ROW_GRIDS)

// For the timer
constexpr int initial_timer_speed = 500;
constexpr int speed_multiplier = 0.1;

enum class Colour {
	Blank,
	Red,
	Green,
	Blue,
	Yellow,
	Cyan,
	Orange,
	Purple
};
// Make sure to update source.cpp if anything is added here
enum class Block {
	Void,
	Single,
	LongUp,
	L,
	ReverseL,
	T,
	Z,
	S
};

// For the canChangeSpot function in game
enum class Direction {
	Left,
	Right,
	Down
};


// STRUCTS
// This is the struct for the grid
struct Grid {
	bool isPlayer;
	Colour colour;
};

// For the __canChangeSpot__ function in Game class
struct ChangeInfo {
	bool changeable;
	bool stick; // this is for like as in stay in it's current position
};

// Namespace
using namespace std;
using BlockMapT = array<array<int, 3>, 3>;
using ColourMapT = array<int, 4>;
using GridT = array<array<Grid, TETRIS_ROW_GRIDS>, TETRIS_COLUMN_GRIDS>;


#endif