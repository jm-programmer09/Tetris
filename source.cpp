#pragma once

#include "tetris.h"
#include <random>
#include <unordered_map>
#include <vector>

// Random Number Generator
// Parse into an enum with static_cast<ENUM_HERE>(return_value_of_function)
static int generateRandNum(int max, int min = 1) {
	// Creating the generator
	random_device device;
	mt19937 gen(device());

	// The range of number distribution
	std::uniform_int_distribution<> dist(min, max);

	// Returning the generated number
	return dist(gen);
}


// This is for assigning maps to each enum
// To get the values do BlockMap.at(Block::Single)
//const unordered_map<Block, vector<BlockMapT>> BlockMap = {
//	make_pair(Block::Single,  BlockMapT {
//		{
//			array<int, 3>{1, 0, 0},
//			array<int, 3>{0, 0, 0},
//			array<int, 3>{0, 0, 0},
//		}
//	}),
//	make_pair(Block::LongUp, BlockMapT {
//		{
//			array<int, 3>{1, 0, 0},
//			array<int, 3>{1, 0, 0},
//			array<int, 3>{1, 0, 0},
//		},
//	}),
//	make_pair(Block::Void, BlockMapT {
//		{
//			array<int, 3>{0, 0, 0},
//			array<int, 3>{0, 0, 0},
//			array<int, 3>{0, 0, 0},
//		}
//	}),
//	make_pair(Block::L, BlockMapT {
//		{
//			array<int, 3>{1, 0, 0},
//			array<int, 3>{1, 0, 0},
//			array<int, 3>{1, 1, 0},
//		}
//	}),
//	make_pair(Block::ReverseL, BlockMapT {
//		{
//			array<int, 3>{0, 1, 0},
//			array<int, 3>{0, 1, 0},
//			array<int, 3>{1, 1, 0},
//		}
//	}),
//	make_pair(Block::Special, BlockMapT {
//		{
//			array<int, 3>{0, 1, 0},
//			array<int, 3>{1, 1, 1},
//			array<int, 3>{0, 0, 0},
//		}
//	})
//};

const unordered_map<Block, vector<BlockMapT>> BlockMap = {
	{Block::Single, vector<BlockMapT> {
		BlockMapT {{
			{1, 0, 0},
			{0, 0, 0},
			{0, 0, 0},
		}}
	}},
	{Block::LongUp, vector<BlockMapT> {
		BlockMapT {{
			{1, 0, 0},
			{1, 0, 0},
			{1, 0, 0},
		}},
		BlockMapT {{
			{1, 1, 1},
			{0, 0, 0},
			{0, 0, 0},
		}}
	}},
	{Block::Void, vector<BlockMapT> {
		BlockMapT {{
			{0, 0, 0},
			{0, 0, 0},
			{0, 0, 0},
		}}
	}},
	{Block::L, vector<BlockMapT> {
		BlockMapT {{
			{1, 0, 0},
			{1, 0, 0},
			{1, 1, 0},
		}},
		BlockMapT {{
			{1, 1, 1},
			{1, 0, 0},
			{0, 0, 0},
		}},
		BlockMapT {{
			{0, 1, 1},
			{0, 0, 1},
			{0, 0, 1}
		}},
		BlockMapT {{
			{0, 0, 0},
			{0, 0, 1},
			{1, 1, 1}
		}},
	}},
	{Block::ReverseL, vector<BlockMapT> {
		BlockMapT {{
			{0, 1, 0},
			{0, 1, 0},
			{1, 1, 0},
		}},
		BlockMapT {{
			{1, 1, 1},
			{0, 0, 1},
			{0, 0, 0},
		}},
		BlockMapT {{
			{1, 1, 0},
			{1, 0, 0},
			{1, 0, 0}
		}},
		BlockMapT {{
			{0, 0, 0},
			{1, 0, 0},
			{1, 1, 1}
		}},
	}},
	{Block::T, vector<BlockMapT> {
		BlockMapT {{
			{0, 1, 0},
			{1, 1, 1},
			{0, 0, 0},
		}},
		BlockMapT {{
			{1, 0, 0},
			{1, 1, 0},
			{1, 0, 0},
		}},
		BlockMapT {{
			{1, 1, 1},
			{0, 1, 0},
			{0, 0, 0}
		}},
		BlockMapT {{
			{0, 0, 1},
			{0, 1, 1},
			{0, 0, 1}
		}},
	}},
	{Block::Z, vector<BlockMapT> {
		BlockMapT {{
			{1, 1, 0},
			{0, 1, 1},
			{0, 0, 0},
		}},
		BlockMapT {{
			{0, 1, 0},
			{1, 1, 0},
			{1, 0, 0},
		}}
	}},
	{Block::S, vector<BlockMapT> {
		BlockMapT {{
			{0, 1, 1},
			{1, 1, 0},
			{0, 0, 0},
		}},
		BlockMapT {{
			{1, 0, 0},
			{1, 1, 0},
			{0, 1, 0},
		}}
	}},
};


// Same process but for the colours
const unordered_map<Colour, ColourMapT> ColourMap = {
	make_pair(Colour::Blank, ColourMapT {
		0, 0, 0, 0
	}),
	make_pair(Colour::Red, ColourMapT {
		255, 0, 0, 255
	}),
	make_pair(Colour::Blue, ColourMapT {
		0, 0, 255, 255
	}),
	make_pair(Colour::Green, ColourMapT {
		0, 255, 0, 255
	}),
	make_pair(Colour::Yellow, ColourMapT {
		255, 255, 0, 255
	}),
	make_pair(Colour::Cyan, ColourMapT {
		0, 0, 255, 255
	}),
	make_pair(Colour::Orange, ColourMapT {
		255, 165, 0, 255
	}),
	make_pair(Colour::Purple, ColourMapT {
		128, 0, 128, 255
	}),
};

