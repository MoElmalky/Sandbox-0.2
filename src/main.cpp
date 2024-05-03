#include "raylib.h"
#include <iostream>
#include <stdlib.h>
#include <vector>

#define AIR 0
#define SAND 1
#define WATER 2
#define STONE 3

int coord(int x, int y);
void swapPixels(int x1,int y1,int x2,int y2);

int SCREEN_WIDTH = 700;
int SCREEN_HEIGHT = 850;
int SCALE_FACTOR = 2;
int ROW_LENGTH = SCREEN_WIDTH / SCALE_FACTOR;
int CLM_LENGTH = SCREEN_HEIGHT / SCALE_FACTOR;

std::vector<int> sandBox(ROW_LENGTH * CLM_LENGTH, AIR);

float circleRadius = SCALE_FACTOR / 2;
int element = 1;

int main(void)
{
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "MALKY");

    SetTargetFPS(120);

    // Main game loop
    while (!WindowShouldClose())
    {

        // Update
        //----------------------------------------------------------------------------------
        int startPointX = (GetMouseX() - circleRadius + SCALE_FACTOR / 2) / SCALE_FACTOR;
        int startPointY = (GetMouseY() - circleRadius + SCALE_FACTOR / 2) / SCALE_FACTOR;
        int endPointX = startPointX + circleRadius * 2 / SCALE_FACTOR;
        int endPointY = startPointY + circleRadius * 2 / SCALE_FACTOR;
        if (startPointX <= 1)
            startPointX = 1;
        if (endPointX >= ROW_LENGTH - 2)
            endPointX = ROW_LENGTH - 2;
        if (GetMouseX() > SCALE_FACTOR && GetMouseX() < SCREEN_WIDTH - SCALE_FACTOR && GetMouseY() >= 0 && GetMouseX() < SCREEN_HEIGHT)
        {
            if (IsMouseButtonDown(MOUSE_BUTTON_LEFT))
            {
                for (int x = startPointX; x <= endPointX; x++)
                {
                    for (int y = startPointY; y <= endPointY; y++)
                    {
                        sandBox[coord(x, y)] = element; // add
                    }
                }
            }
            else if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
            {
                for (int x = startPointX; x <= endPointX; x++)
                {
                    for (int y = startPointY; y <= endPointY; y++)
                    {
                        sandBox[coord(x, y)] = AIR; // remove
                    }
                }
            }
        }
        if (IsKeyPressed(KEY_BACKSPACE))
            sandBox.assign(ROW_LENGTH * CLM_LENGTH, AIR); // clear the window

        if (IsKeyDown(KEY_EQUAL) && circleRadius < 100)
            circleRadius += SCALE_FACTOR; // increase the circle size
        else if (IsKeyDown(KEY_MINUS) && circleRadius > SCALE_FACTOR)
            circleRadius -= SCALE_FACTOR; // decrease the circle size

        if (IsKeyPressed(KEY_ONE))
            element = SAND;
        else if (IsKeyPressed(KEY_TWO))
            element = WATER;
        else if (IsKeyPressed(KEY_THREE))
            element = STONE;
        
        if(IsKeyDown(KEY_Q))
        {
            for (int y = CLM_LENGTH - 1; y > 0; y--)
        {
            for (int x = ROW_LENGTH - 1; x > 0; x--)
            {
                if(sandBox[coord(x,y)]==SAND)
                    sandBox[coord(x,y)]=AIR;
            }
        }
        }
        else if(IsKeyDown(KEY_W))
        {
            for (int y = CLM_LENGTH - 1; y > 0; y--)
        {
            for (int x = ROW_LENGTH - 1; x > 0; x--)
            {
                if(sandBox[coord(x,y)]==WATER)
                    sandBox[coord(x,y)]=AIR;
            }
        }
        }
        else if(IsKeyDown(KEY_E))
        {
            for (int y = CLM_LENGTH - 1; y > 0; y--)
        {
            for (int x = ROW_LENGTH - 1; x > 0; x--)
            {
                if(sandBox[coord(x,y)]==STONE)
                    sandBox[coord(x,y)]=AIR;
            }
        }
        }

        for (int y = CLM_LENGTH - 1; y > 0; y--)
        {
            for (int x = ROW_LENGTH - 1; x > 0; x--)
            {
                // sand sim
                if (sandBox[coord(x, y)] == SAND)
                {
                    int rand = GetRandomValue(0, 1) * 2 - 1;
                    int rand2 = GetRandomValue(0, 1);
                    if (sandBox[coord(x, y + 1)] == AIR && y < CLM_LENGTH - 1)
                        swapPixels(x,y+1,x,y);
                    else if (sandBox[coord(x + rand, y + 1)] == AIR && x + rand < ROW_LENGTH - 1 && x + rand > 0)
                        swapPixels(x+rand,y+1,x,y);
                    else if (sandBox[coord(x - rand, y + 1)] == AIR && x - rand < ROW_LENGTH - 1 && x - rand > 0)
                        swapPixels(x-rand,y+1,x,y);
                    else if(sandBox[coord(x, y + 1)] == WATER && y < CLM_LENGTH - 1)
                        swapPixels(x+rand*rand2,y+rand2,x,y);
                    else if(sandBox[coord(x + rand, y + 1)] == WATER && x + rand < ROW_LENGTH - 1 && x + rand > 0)
                        swapPixels(x+rand*rand2,y+rand2,x,y);
                    else if(sandBox[coord(x - rand, y + 1)] == WATER && x - rand < ROW_LENGTH - 1 && x - rand > 0)
                        swapPixels(x-rand*rand2,y+rand2,x,y);
                }
                // water sim
                else if (sandBox[coord(x, y)] == WATER)
                {
                    int rand = GetRandomValue(0, 1) * 2 - 1;
                    if (sandBox[coord(x, y + 1)] == AIR && y < CLM_LENGTH - 1)
                        swapPixels(x,y+1,x,y);
                    else if (sandBox[coord(x + rand, y + 1)] == AIR && x + rand < ROW_LENGTH - 1 && x + rand > 0)
                        swapPixels(x + rand, y + 1,x,y);
                    else if (sandBox[coord(x - rand, y + 1)] == AIR && x - rand < ROW_LENGTH - 1 && x - rand > 0)
                        swapPixels(x - rand, y + 1,x,y);
                    else if (sandBox[coord(x + 1, y)] == AIR && x - rand < ROW_LENGTH - 3 && x - rand > 0)
                        swapPixels(x + 1, y,x,y);
                }
            }
        }
        // Draw
        //----------------------------------------------------------------------------------
        BeginDrawing();
        ClearBackground(BLACK);
        DrawFPS(1, 1);
        if (element == SAND)
            DrawText("Sand", 340, 10, 24, GetColor(0xFDDE55FF));
        else if (element == WATER)
            DrawText("Water", 340, 10, 24, GetColor(0x0E46A3FF));
        else if (element == STONE)
            DrawText("Stone", 340, 10, 24, GetColor(0x9290C3FF));
        for (int y = 0; y < CLM_LENGTH; y++)
        {
            for (int x = 0; x < ROW_LENGTH; x++)
            {
                if (sandBox[coord(x, y)] == SAND)
                    DrawRectangle(x * SCALE_FACTOR, y * SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR, GetColor(0xFDDE55FF));
                else if (sandBox[coord(x, y)] == WATER)
                    DrawRectangle(x * SCALE_FACTOR, y * SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR, GetColor(0x0E46A3FF));
                else if (sandBox[coord(x, y)] == STONE)
                    DrawRectangle(x * SCALE_FACTOR, y * SCALE_FACTOR, SCALE_FACTOR, SCALE_FACTOR, GetColor(0x9290C3FF));
            }
        }
        DrawCircleLines(GetMouseX(), GetMouseY(), circleRadius, WHITE);
        EndDrawing();
    }
    CloseWindow();
    return 0;
}

int coord(int x, int y)
{
    return x + y * ROW_LENGTH;
}

void swapPixels(int x1,int y1,int x2,int y2){
    int temp = sandBox[coord(x1,y1)];
    sandBox[coord(x1,y1)] = sandBox[coord(x2,y2)];
    sandBox[coord(x2,y2)] = temp;
}