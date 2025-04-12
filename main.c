#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 600;

typedef struct {
    float ballX;
    float ballY;
    int ball_speed_x;
    int ball_speed_y;
    int ball_radius;
} Ball;


void draw_ball(Ball ball){
    DrawCircle(ball.ballX, ball.ballY, ball.ball_radius, WHITE);
}


void ball_movement(Ball *ball){
    ball->ballX += ball->ball_speed_x;
    ball->ballY += ball->ball_speed_y;

    // "bouncing of edges", changing direction of the ball if met with the edge of the screen
    if (ball->ballX + ball->ball_radius >= screenWidth || ball->ballX - ball->ball_radius <= 0) {
        ball->ball_speed_x *= -1;
    }

    if (ball->ballY + ball->ball_radius >= screenHeight || ball->ballY - ball->ball_radius <= 0) {
        ball->ball_speed_y *= -1;
    }
}


typedef struct {
    float x;
    float y;
    float width;
    float height;
    int speed;
} Paddle;


void draw_paddle(Paddle paddle){
    DrawRectangle(paddle.x, paddle.y, paddle.width, paddle.height, WHITE);
}

void player_paddle_movement(Paddle *paddle){

    if (IsKeyDown(KEY_W) || IsKeyDown(KEY_UP)){
        paddle->y -= paddle->speed;
    } else if (IsKeyDown(KEY_S) || IsKeyDown(KEY_DOWN)){
        paddle->y += paddle->speed;
    }


    // stopping ability to go off screen
    if (paddle->y >= screenHeight - paddle->height){
        paddle->y = screenHeight - paddle->height;
    } else if (paddle->y <= 0){
        paddle->y = 0;
    }
}

void enemy_paddle_movement(Paddle *paddle, Ball *ball){
    if (paddle->y + paddle->height / 2 > ball->ballY){
        paddle->y = paddle->y - paddle->speed;
    } 
    else if (paddle->y + paddle->height / 2 <= ball->ballY){
        paddle->y = paddle->y + paddle->speed;
    }

    // stopping ability to go off screen
    if (paddle->y >= screenHeight - paddle->height){
        paddle->y = screenHeight - paddle->height;
    } else if (paddle->y <= 0){
        paddle->y = 0;
    }
}


Ball ball;
Paddle player;
Paddle enemy;


int main(void)
{

    InitWindow(screenWidth, screenHeight, "PING PONG");

    SetTargetFPS(60);

    // variables
    ball.ballX = 100;
    ball.ballY = 100;
    ball.ball_speed_x = 5;
    ball.ball_speed_y = 5;
    ball.ball_radius = 10;

    player.x = screenWidth - player.width - 35;
    player.y = screenHeight / 2 - player.height / 2;
    player.width = 25;
    player.height = 120;
    player.speed = 6;

    enemy.x = 10;
    enemy.y = screenHeight / 2 - 50;
    enemy.width = 25;
    enemy.height = 120;
    enemy.speed = 6;

    while (!WindowShouldClose())
    {
        // event handling


        // updating positions
        
        
        // draw
        BeginDrawing();

            ClearBackground(VIOLET);
            DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);

            draw_ball(ball);
            ball_movement(&ball);

            // enemy
            draw_paddle(enemy);
            enemy_paddle_movement(&enemy, &ball);

            // player
            draw_paddle(player);
            player_paddle_movement(&player);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}