#include "raylib.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

int main(void)
{
    const int SCREEN_WIDTH = 500;
    const int SCREEN_HEIGHT = 500;
    const int TILE_WIDTH = 5;
    const int TILE_HEIGHT = TILE_WIDTH;
    const int ROW_TILES = SCREEN_WIDTH / TILE_WIDTH;
    const int COLUMN_TILES = SCREEN_HEIGHT / TILE_HEIGHT;
    float circleRadius = TILE_WIDTH / 2;

    std::vector<std::vector<char>> sandBox(ROW_TILES, std::vector<char>(COLUMN_TILES, '0'));

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MALKY");

    SetTargetFPS(60);

    // Main game loop
    while (!WindowShouldClose())
    {

        // Update
        //----------------------------------------------------------------------------------
        int startPointX = (GetMouseX() - circleRadius + TILE_WIDTH / 2) / TILE_WIDTH;
        int startPointY = (GetMouseY() - circleRadius + TILE_WIDTH / 2) / TILE_WIDTH;
        int endPointX = startPointX + circleRadius * 2 / TILE_WIDTH;
        int endPointY = startPointY + circleRadius * 2 / TILE_WIDTH;
        if(startPointX<=TILE_WIDTH)
           startPointX=TILE_WIDTH;
        if(endPointX>=ROW_TILES-TILE_WIDTH)
            endPointX=ROW_TILES-TILE_WIDTH;
        if (GetMouseX() > TILE_WIDTH && GetMouseX() < SCREEN_WIDTH - TILE_WIDTH && GetMouseY() >= 0 && GetMouseX() < SCREEN_HEIGHT)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                for (int i = startPointX; i <= endPointX; i++)
                {
                    for (int j = startPointY; j <= endPointY; j++)
                    {
                        sandBox[i][j] = '1';
                    }
                }
                // sandBox[GetMouseX() / TILE_HEIGHT][GetMouseY() / TILE_HEIGHT] = '1';
            }
            else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
            {

                for (int i = startPointX; i < endPointX; i++)
                {
                    for (int j = startPointY; j < endPointY; j++)
                    {
                        sandBox[i][j] = '0';
                    }
                }
                // sandBox[GetMouseX() / TILE_HEIGHT][GetMouseY() / TILE_HEIGHT] = '0';
            }
        }
        if (IsKeyPressed(KEY_BACKSPACE))
        {
            sandBox.assign(ROW_TILES, std::vector<char>(COLUMN_TILES, '0'));
        }
        if (IsKeyPressed(KEY_EQUAL) && circleRadius < 100)
            circleRadius += TILE_WIDTH;
        if (IsKeyPressed(KEY_MINUS) && circleRadius > TILE_WIDTH)
            circleRadius -= TILE_WIDTH;

        std::vector<std::vector<char>> nextSandBox(sandBox);
        for (int i = 0; i < ROW_TILES; i++)
        {
            for (int j = 0; j < COLUMN_TILES; j++)
            {
                if (sandBox[i][j] == '1')
                {
                    int rand = GetRandomValue(0, 1) * 2 - 1;
                    if (sandBox[i][j + 1] == '0')
                    {
                        if (j < COLUMN_TILES - 1)
                        {
                            nextSandBox[i][j + 1] = '1';
                            nextSandBox[i][j] = '0';
                        }
                    }
                    else if (sandBox[i + rand][j + 1] == '0')
                    {
                        if (i + rand < ROW_TILES - 1 && i + rand > 0)
                        {
                            nextSandBox[i + rand][j + 1] = '1';
                            nextSandBox[i][j] = '0';
                        }
                    }
                    else if (sandBox[i - rand][j + 1] == '0')
                    {
                        if (i - rand < ROW_TILES - 1 && i - rand > 0)
                        {
                            nextSandBox[i - rand][j + 1] = '1';
                            nextSandBox[i][j] = '0';
                        }
                    }
                }
            }
        }
        sandBox = nextSandBox;

        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);
        DrawCircleLines(GetMouseX(), GetMouseY(), circleRadius, WHITE);
        DrawFPS(1, 1);
        for (int i = 0; i < ROW_TILES; i++)
        {
            for (int j = 0; j < COLUMN_TILES; j++)
            {
                if (sandBox[i][j] == '1')
                    DrawRectangle(i * TILE_WIDTH, j * TILE_HEIGHT, TILE_WIDTH, TILE_HEIGHT, WHITE);
            }
        }

        EndDrawing();
    }
    CloseWindow();

    return 0;
}