#include "core/Game.h"

int main() {
    Game game;

    // Initialize game window and systems
    game.Init();

    // Start the main game loop
    game.Run();

    // Clean up and close window
    game.Close();

    return 0;
}
