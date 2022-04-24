#include "raylib.h"

#include "snakecontroller.hpp"
#include "population.hpp"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 500;
    const int screenHeight = 500;
    
    InitWindow(screenWidth, screenHeight, "Snake");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    Snakecontroller game = Snakecontroller(50, 50);
    SetTargetFPS(24);

    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        if (game.getGameStatus() == ALIVE) {
            game.readInput();
            game.update();
        }

        if (IsKeyPressed(KEY_R))
            game.newGame();

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            game.draw();

            if (game.getGameStatus() == DEAD) {
                DrawText("L", GetScreenWidth()/2 - MeasureText("L", 300)/2, GetScreenHeight()/2 - 50, 300, PINK);
            }

        EndDrawing();
    }

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}