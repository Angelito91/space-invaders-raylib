#include "Game.h"

int main() {
    Game game;

    // Initialize game window and systems
    game.init();

    // Start the main game loop
    game.run();

    // Clean up and close window
    Game::close();

    return 0;
}