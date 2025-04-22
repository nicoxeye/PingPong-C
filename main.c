#include "raylib.h"

const int screenWidth = 800;
const int screenHeight = 600;

typedef enum GameScreen { TITLE = 0, GAMEPLAY} GameScreen;

typedef struct {
    float ballX;
    float ballY;
    int ball_speed_x;
    int ball_speed_y;
    int ball_radius;
} Ball;

typedef struct{
    int player;
    int enemy;
} Score;


void reset_ball(Ball *ball){
    ball->ballX = screenWidth / 2;
    ball->ballY = screenHeight / 2;

    int choice[2] = {-1, 1};
    ball->ball_speed_x *= choice[GetRandomValue(0, 1)];
    ball->ball_speed_y *= choice[GetRandomValue(0, 1)];
}


void draw_ball(Ball ball){
    DrawCircle(ball.ballX, ball.ballY, ball.ball_radius, WHITE);
}


void ball_movement(Ball *ball, Score *score){
    ball->ballX += ball->ball_speed_x;
    ball->ballY += ball->ball_speed_y;

    // "bouncing of edges", changing direction of the ball if met with the edge of the screen
    if (ball->ballY + ball->ball_radius >= screenHeight || ball->ballY - ball->ball_radius <= 0) {
        ball->ball_speed_y *= -1;
    }
    //scoring
    if (ball->ballX + ball->ball_radius >= screenWidth) {
        score->enemy++;

        reset_ball(ball);
    }
    if (ball->ballX - ball->ball_radius <= 0){
        score->player++;

        reset_ball(ball);
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
Score score;


int main(void)
{
    GameScreen currentScreen = TITLE;
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

    score.enemy = 0;
    score.player = 0;

    while (!WindowShouldClose())
    {
        switch(currentScreen){
            case TITLE:
                if (IsKeyPressed(KEY_SPACE))
                {
                    currentScreen = GAMEPLAY;
                }
            break;
            case GAMEPLAY:
            break;
            default: break;
        }
        BeginDrawing();
            ClearBackground(BLACK);

            switch(currentScreen){
                case TITLE:
                    DrawText("TITLE SCREEN", 20, 20, 40, WHITE);
                    DrawText("PRESS SPACE TO PLAY", 120, 220, 20, WHITE);
                break;
                case GAMEPLAY:                        
                    const char *scoreText = "SCORE";
                    int fontSize = 40;
                    int textWidth = MeasureText(scoreText, fontSize);
                    DrawText(scoreText, (screenWidth - textWidth) / 2, 10, fontSize, WHITE);

                    
                    DrawLine(screenWidth / 2, 0, screenWidth / 2, screenHeight, WHITE);

                    draw_ball(ball);
                    ball_movement(&ball, &score);

                    // enemy
                    draw_paddle(enemy);
                    enemy_paddle_movement(&enemy, &ball);

                    // player
                    draw_paddle(player);
                    player_paddle_movement(&player);
                    DrawText(TextFormat("%d", score.player), screenWidth* 3/ 4, 100, 40, WHITE);
                    DrawText(TextFormat("%d", score.enemy), screenWidth / 4, 100, 40, WHITE);

                    Vector2 vector = {ball.ballX, ball.ballY};
                    Rectangle rectangle = {player.x, player.y, player.width, player.height};

                    // collisison of paddles
                    if (CheckCollisionCircleRec(vector, ball.ball_radius, rectangle)){
                        ball.ball_speed_x *= -1;
                    }

                    Rectangle rectangle_enemy = {enemy.x, enemy.y, enemy.width, enemy.height};

                    if (CheckCollisionCircleRec(vector, ball.ball_radius, rectangle_enemy)){
                        ball.ball_speed_x *= -1;
                    }
                break;
                default: break;
            }


        EndDrawing();
    }

    CloseWindow();

    return 0;
}