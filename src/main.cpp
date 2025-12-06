#include "raylib.h"
#include <raymath.h>
#include <deque> // To use for snake body segments
#include <cstdio> // For Linux Build

#include "Game.hpp"

int main(int argc, char**argv) {
    Game game = init_game();
	game_loop(game);

    CloseWindow();
    return 0;

}
