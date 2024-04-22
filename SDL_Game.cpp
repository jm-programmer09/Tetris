#include <SDL.h>
#include "tetris.h"
#include "player.h"
#include "source.cpp"

// TODO
// Have to start detecting whether the lines are able to be cleared and recieve points
// We have to have the point where the user loses
// In the flip function we have to change the tetris objects to prevent it from flipping onto other objects

class Game {
public:
    GridT grid;
    Player player;

    Game(SDL_Renderer* renderer) :
        // Player initialisation
        player(0, 0)
    {
        this->canvas = renderer;
        
        // Loading the grid initially
        for (int column_index = 0; column_index < TETRIS_COLUMN_GRIDS; column_index++) {
            // This is the row part here { 0, 0, 0, 1, 0} type thing
            for (int row_index = 0; row_index < TETRIS_ROW_GRIDS; row_index++) {
                // Adding the grid items
                grid[column_index][row_index] = { false, Colour::Blank };
            }
        }

        // THE REASON WHY THE OBJECT IS DISAPPEARING MIGHT HAVE SOMETHING TO DO WITH THE RENDER OF THE PLAYER MAP

        // This is the timer for the moving down of the tetris element
        SDL_TimerID timer = SDL_AddTimer(500, [](Uint32 interval, void* param) -> Uint32 {
            // Game instasnce
            Game* gameInstance = static_cast<Game*>(param);

            // TO make sure it can move down without any errors
            if (gameInstance->canChangeSpot(Direction::Down)) {
                // Clearing the last position
                gameInstance->changePlayer(Colour::Blank);

                // Changing the players position
                gameInstance->player.y++;
            }

            return interval;
        }, this);

        if (timer == 0) {
            SDL_Log("Failed to create player interval timer");
        }

    }


    void render() {
        // WOULD WE BE ABLE TO OPTIMIZE BY PUTTING THE RENDER OF THE ACTUAL GRID COMBINED WITH THE PLAYER RENDER?

        // Adding the current Player render to the grid can also be used to delete the old player

        changePlayer(player.colour);

        // RENDERING THE GRID
        for (int column_index = 0; column_index < TETRIS_ROW_GRIDS; column_index++) {
            for (int row_index = 0; row_index < TETRIS_ROW_GRIDS; row_index++) {
                SDL_Rect grid_block = { GRID_SIZE * row_index, GRID_SIZE * column_index, GRID_SIZE, GRID_SIZE };

                // This is where Colour::Blank is used
                ColourMapT block_colour_properties = ColourMap.at(grid[column_index][row_index].colour);

                SDL_SetRenderDrawColor(canvas, block_colour_properties[0], block_colour_properties[1], block_colour_properties[2], block_colour_properties[3]);

                SDL_RenderFillRect(canvas, &grid_block);
            }
        }        
    }

    // For clearing the last position of the player - make sure to move the player after the function has been executed
    void changePlayer(Colour colour, bool isPlayer = true) {
        // This can be used to add the player to the grid too

        for (int column_index = 0; column_index < (sizeof(player.player_map) / sizeof(player.player_map[0])); column_index++) {
            // To iterate over the row
            for (int row_index = 0; row_index < (sizeof(player.player_map[0]) / sizeof(player.player_map[0][0])); row_index++) {
                if (player.player_map[column_index][row_index] == 0) continue;
                
                // Rendering the components
                grid.at(player.y + column_index).at(player.x + row_index) = { isPlayer, colour };
            }
        }
    }

    // This is the function that checks if an element can be moved left or right or down and if it is colliding with any external objects
    bool canChangeSpot(Direction direction) {

        // Running through every grid of the player.player_map
        for (int pmap_columnI = 0; pmap_columnI < (sizeof(player.player_map) / sizeof(player.player_map[0])); pmap_columnI++) {
            for (int pmap_rowI = 0; pmap_rowI < (sizeof(player.player_map[0]) / sizeof(player.player_map[0][0])); pmap_rowI++) {
                // To iterate over each cube in the map
                if (player.player_map[pmap_columnI][pmap_rowI] == 0) continue; // To skip if it isnt a render of the player

                int x = player.x + pmap_rowI; // Before adding the direction changes
                int y = player.y + pmap_columnI; 

                // For the additions
                int next_x;
                int next_y;

                switch (direction) {

                case Direction::Left:
                    next_x = x - 1;

                    // Checking for collision on wall
                    if (next_x < 0) { return false; }

                    if (grid.at(y).at(next_x).colour != Colour::Blank && !grid.at(y).at(next_x).isPlayer) {
                        return false;
                    }

                    break;

                case Direction::Right:
                    next_x = x + 1;

                    // For preventing it from hitting the right wall
                    if (x >= TETRIS_ROW_GRIDS-1) {
                        return false; 
                    }
                   
                    // Else
                    if (grid.at(y).at(next_x).colour != Colour::Blank && !grid.at(y).at(next_x).isPlayer) {
                        return false;
                    }
                    break;

                case Direction::Down:
                    next_y = y + 1;

                    // Detecting bottom border
                    if (y >= TETRIS_COLUMN_GRIDS-1) {
                        stick_player();
                        return false;
                    }

                    // Detecting objects below
                    if (grid.at(next_y).at(x).colour != Colour::Blank && !grid.at(next_y).at(x).isPlayer) {
                        stick_player();
                        return false;
                    } 

                    break;
                }
            }
        }

        // Keep as if the player makes it then it can move
        return true;
    }


    // This is for flipping the player and detecting whether the flip is possible
    void flip() {
        // Making sure that the player doesnt flip to a stage that isnt available
        SDL_Log(to_string(BlockMap.at(player.block).size()).c_str());
        if (player.current_rotation + 1 >= BlockMap.at(player.block).size()) {
            player.current_rotation = 0;
        }
        else {
            player.current_rotation++;
        }
        try {
            player.player_map = BlockMap.at(player.block)[player.current_rotation];
        }
        catch (const out_of_range& error) {
            // Pass
            return;
        }
    }

private:
    SDL_Renderer* canvas;

    // get the player to stick
    void stick_player() {
        changePlayer(player.colour, false);

        // Creating the new player
        player = Player(TETRIS_CENTER, 0);
    }
};

// MAIN
int SDL_main(int argc, char* argv[]) {
    // Initialising the SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        SDL_Log("SDL initialization failed: %s", SDL_GetError());
        return 1;
    }

    // Create the window and the canvas
    SDL_Window* window = SDL_CreateWindow("Tetris", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH, WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (!window) {
        SDL_Log("Window initialisation failed: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // The canvas
    SDL_Renderer* canvas = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (!canvas) {
        SDL_Log("Renderer (canvas) failed to load: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    //switch (static_cast<Block>(generateRandNum(0, 0))) {
    //case Block::Void:
    //    SDL_Log("Void");
    //}

    Game game = Game(canvas);


    // Game rendering loop until user shutdown
    bool quit = false;
    SDL_Event event;

    do {
        SDL_SetRenderDrawColor(canvas, 0, 0, 0, 255);
        SDL_RenderClear(canvas);

        // Rendering items
        game.render();

        SDL_RenderPresent(canvas);

        // Event Management 
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT: quit = true; break;
                
                // Add in the buttons here
                case SDL_KEYDOWN:
                    // Key checking
                    switch (event.key.keysym.sym) {
                        // Moving left   
                        // make sure the clear the last position of the player 
                        case SDLK_a:
                            if (!game.canChangeSpot(Direction::Left)) { continue; }
                            game.changePlayer(Colour::Blank); // to clear it for the movement it is actually rendered in the render function
                            game.player.x--;
                            break;
                        case SDLK_d:
                            if (!game.canChangeSpot(Direction::Right)) { continue;  }
                            game.changePlayer(Colour::Blank);
                            game.player.x++;
                            break;
                        // Down
                        case SDLK_s:
                            if (!game.canChangeSpot(Direction::Down)) { continue; }
                            game.changePlayer(Colour::Blank);
                            game.player.y++;
                            break;
                        // Flipping the objects
                        case SDLK_w:
                            game.changePlayer(Colour::Blank);
                            game.flip();

                            break;
                    }

            }
        }

    } while (!quit);

    // Cleanup and quit SDL
    SDL_DestroyRenderer(canvas);
    SDL_DestroyWindow(window);
    SDL_Quit();

    return 0;
}