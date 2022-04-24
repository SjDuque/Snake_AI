/*******************************************************************************************
*
*   raylib [textures] example - Texture loading and drawing
*
*   This example has been created using raylib 1.0 (www.raylib.com)
*   raylib is licensed under an unmodified zlib/libpng license (View raylib.h for details)
*
*   Copyright (c) 2014 Ramon Santamaria (@raysan5)
*
********************************************************************************************/

#include "raylib.h"

#include "snake.hpp"
#include "snakecontroller.hpp"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 500;
    const int screenHeight = 500;
    
    InitWindow(screenWidth, screenHeight, "Snake");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)

    Snakecontroller game = Snakecontroller(30, 30);
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
            game = Snakecontroller(30, 30);

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