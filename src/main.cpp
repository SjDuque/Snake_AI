#include "raylib.h"

#include "snake_game.hpp"
#include "brain.hpp"
#include "player.hpp"
#include "population.hpp"
#include "feature_extractor.hpp"

#include <iostream>

using namespace std;
int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 1000;
    const int MAX_MOVES = 100;
    
    InitWindow(screenWidth, screenHeight, "Snake");
    vector<int> dims = {extractFeaturesSize(), 10, 10, 5, 3};
    Population pop(dims, 2500, 0.1);
    Brain brain(dims);
    Player play;
    ControllerI* input = &pop;
    srand(time(NULL));
    SnakeGame game = SnakeGame(input, 32, 32, 3, 5);
    SetTargetFPS(120);

    while (!WindowShouldClose())
    {
        if (game.getStatus() == ALIVE) {
            game.update();
        }

        if (IsKeyPressed(KEY_R) || game.getMoves() > MAX_MOVES) {
            game.newGame();
        }
        
        BeginDrawing();

            ClearBackground(RAYWHITE);

            game.draw();

            if (game.getStatus() == DEAD) {
                DrawText("L", GetScreenWidth()/2 - MeasureText("L", 300)/2, GetScreenHeight()/2 - MeasureText("L", 300)/2, 300, BLUE);
                game.newGame();
            }

        EndDrawing();
    }

    CloseWindow();

    return 0;
}