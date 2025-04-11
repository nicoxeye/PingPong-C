#include "raylib.h"

int main(void)
{
    const int screenWidth = 800;
    const int screenHeight = 600;

    InitWindow(screenWidth, screenHeight, "PING PONG");

    SetTargetFPS(60);

    // variables
    int ballX = 100;
    int ballY = 100;
    int ball_speed_x = 5;
    int ball_speed_y = 5;
    int ball_radius = 10;

    while (!WindowShouldClose())
    {
        // event handling


        // updating positions
        
        
        // draw
        BeginDrawing();

            ClearBackground(BLACK);

            ballX += ball_speed_x;
            ballY += ball_speed_y;

            if (ballX + ball_radius >= screenWidth || ballX - ball_radius <= 0){
                ball_speed_x *= -1;
            }

            if (ballY + ball_radius >= screenHeight || ballY - ball_radius <= 0){
                ball_speed_y *= -1;
            }
        
        DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);
        DrawCircle(ballX, ballY, ball_radius, WHITE);
        DrawRectangle(10, screenHeight / 2 - 50, 20, 100, WHITE);
        DrawRectangle(screenWidth - 30, screenHeight / 2 - 50, 20, 100, WHITE);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}