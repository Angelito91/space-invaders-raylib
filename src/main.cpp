#include <raylib.h>

int main() {
    // Inicializar ventana
    InitWindow(800, 600, "space-invaders");
    SetTargetFPS(60);

    // Variables del juego
    Vector2 playerPos = {400, 300};
    int playerSize = 20;

    // Loop principal
    while (!WindowShouldClose()) {
        // Entrada
        if (IsKeyDown(KEY_RIGHT)) playerPos.x += 5;
        if (IsKeyDown(KEY_LEFT)) playerPos.x -= 5;
        if (IsKeyDown(KEY_DOWN)) playerPos.y += 5;
        if (IsKeyDown(KEY_UP)) playerPos.y -= 5;

        // Renderizado
        BeginDrawing();
        ClearBackground(BLACK);

        DrawCircle(playerPos.x, playerPos.y, playerSize, GREEN);
        DrawText("¡Hola Raylib!", 10, 10, 20, WHITE);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
