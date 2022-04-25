#include "raylib.h"

#include "snake_game.hpp"
#include "brain.hpp"
#include "player.hpp"
#include "feature_extractor.hpp"

#include <iostream>

using namespace std;
int main(void)
{
    const int screenWidth = 1000;
    const int screenHeight = 1000;
    
    InitWindow(screenWidth, screenHeight, "Snake");
    vector<int> dims = {50, 100, 3};
    Brain b(dims);
    // Player p;
    ControllerI* input = &b;
    Snake snake;
    SnakeGame game = SnakeGame(input, 32, 32, 3, 5);
    SetTargetFPS(120);

    while (!WindowShouldClose())
    {
        if (game.getStatus() == ALIVE) {
            game.update();
        }

        if (IsKeyPressed(KEY_R)) {
            b = Brain(b, 0.1);
            input = &b;
            game.newGame();
        }
        
        BeginDrawing();

            ClearBackground(RAYWHITE);

            game.draw();

            if (game.getStatus() == DEAD) {
                DrawText("L", GetScreenWidth()/2 - MeasureText("L", 300)/2, GetScreenHeight()/2 - MeasureText("L", 300)/2, 300, BLUE);
                b = Brain(b, 0.1);
                input = &b;
                game.newGame();
            }
            // cout << p.getNextMove(snake) << endl;

        EndDrawing();
    }

    CloseWindow();

    return 0;
}