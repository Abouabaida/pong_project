#include "view.h"

int check_collision(ball_t a, paddle_t b)
{
    int left_a, left_b;
    int right_a, right_b;
    int top_a, top_b;
    int bottom_a, bottom_b;

    left_a = a.x;
    right_a = a.x + a.w;
    top_a = a.y;
    bottom_a = a.y + a.h;

    left_b = b.x;
    right_b = b.x + b.w;
    top_b = b.y;
    bottom_b = b.y + b.h;

    if ((left_a > right_b) || (right_a < left_b) || (top_a > bottom_b) || (bottom_a < top_b))
        return 0;
    return 1;
}

void Controle_ball(game_t *game)
{

    game->ball.x += game->ball.dx;
    game->ball.y += game->ball.dy;

    if (game->ball.x < 0)
    {
        game->score[1] += 1;
        init_ball(game);
    }

    if (game->ball.x > game->screen->w - 10)
    {
        game->score[0] += 1;
        init_ball(game);
    }

    if (game->ball.y < 0 || game->ball.y > game->screen->h - 10)

        game->ball.dy = -game->ball.dy;


    int i;

    for (i = 0; i < 2; i++)
    {
        if (check_collision(game->ball, game->paddle[i]) == 1)
        {
            if (game->ball.dx < 0)
                game->ball.dx -= 1;
            else
                game->ball.dx += 1;
            game->ball.dx = -game->ball.dx;
            int hit_pos = (game->paddle[i].y + game->paddle[i].h) - game->ball.y;

            if (hit_pos >= 0 && hit_pos < 7)
                game->ball.dy = 4;
            if (hit_pos >= 7 && hit_pos < 14)
                game->ball.dy = 3;
            if (hit_pos >= 14 && hit_pos < 21)
                game->ball.dy = 2;
            if (hit_pos >= 21 && hit_pos < 28)
                game->ball.dy = 1;
             if (hit_pos >= 28 && hit_pos < 32)
                game->ball.dy = 0;
            if (hit_pos >= 32 && hit_pos < 39)
                game->ball.dy = -1;
            if (hit_pos >= 39 && hit_pos < 46)
                game->ball.dy = -2;
            if (hit_pos >= 46 && hit_pos < 53)
                game->ball.dy = -3;
            if (hit_pos >= 53 && hit_pos <= 60)
                game->ball.dy = -4;
            if (game->ball.dx > 0)
            {
                if (game->ball.x < 30)
                    game->ball.x = 30;
            }
            else
             {

               if (game->ball.x > 600)
                    game->ball.x = 600;
             }
        }
    }
}
int IsGameOver(game_t *game)
{

        if (game->score[0] == 10 )
        {
            game->score[0] = 0;
            game->score[1] = 0;
            return PLAYER_1_WIN;
        }
        if (game->score[1] == 10 )
        {
            game->score[0] = 0;
            game->score[1] = 0;
            return PLAYER_2_WIN;
        }
    return NO_GAMEOVER;
}
void Controle_paddle(game_t *game,int key_pressed)
{

    if (key_pressed == KEY_DOWN)
    {
        if(game->paddle[1].y >= game->screen->h - game->paddle[1].h)
            game->paddle[1].y = game->screen->h - game->paddle[1].h;
        else
            game->paddle[1].y += 5;
    }

    if (key_pressed == KEY_UP)
    {
        if(game->paddle[1].y <= 0)
            game->paddle[1].y = 0;
        else
            game->paddle[1].y -= 5;
    }
}
