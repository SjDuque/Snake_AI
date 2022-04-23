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
#include "Eigen/Dense"

#include "snake.hpp"
#include "snakecontroller.hpp"

int main(void)
{
    // Initialization
    //--------------------------------------------------------------------------------------
    const int screenWidth = 800;
    const int screenHeight = 450;
    
    Eigen::MatrixXf a(50, 50);
    InitWindow(screenWidth, screenHeight, "raylib [textures] example - texture loading and drawing");

    // NOTE: Textures MUST be loaded after Window initialization (OpenGL context is required)
    Texture2D texture = LoadTexture("assets/raylib_logo.png");        // Texture loading

    Snakecontroller game = Snakecontroller(50, 30);

    //---------------------------------------------------------------------------------------

    // Main game loop
    while (!WindowShouldClose())    // Detect window close button or ESC key
    {
        // Update
        //----------------------------------------------------------------------------------
        // TODO: Update your variables here
        //----------------------------------------------------------------------------------
        if (game.getGameStatus() == ACTIVE) {
            game.readInput();
            game.update();
        }

        if (IsKeyPressed(KEY_R))
            game = Snakecontroller(50, 30);

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();

            ClearBackground(RAYWHITE);

            game.draw();

            if (game.getGameStatus() == COLLIDED) {
                DrawText("L", GetScreenWidth()/2 - MeasureText("L", 300)/2, GetScreenHeight()/2 - 50, 300, PINK);
            }

        EndDrawing();
        //----------------------------------------------------------------------------------
        WaitTime(100);
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(texture);       // Texture unloading

    CloseWindow();                // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}