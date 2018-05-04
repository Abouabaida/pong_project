#include <stdlib.h>
#include <stdio.h>
#include "view.h"

void init_ball(game_t *game)
{

    game->ball.x = game->screen->w / 2;
    game->ball.y = game->screen->h / 2;
    game->ball.w = 10;
    game->ball.h = 10;
    game->ball.dy = 1;
    game->ball.dx = 1;

    game->paddle[0].x = 20;
    game->paddle[0].y = game->screen->h / 2 - 50 ;
    game->paddle[0].w = 10;
    game->paddle[0].h = 50;

    game->paddle[1].x = game->screen->w - 20 - 10;
    game->paddle[1].y = game->screen->h / 2 - 50;
    game->paddle[1].w = 10;
    game->paddle[1].h = 50;
}

int Game_Engine(game_t *game)
{
    Uint8 *keystate = 0;

    keystate = SDL_GetKeyState(NULL);

    if (keystate[SDLK_ESCAPE])
    {
        game->state = QUIT;
    }
    if (keystate[SDLK_DOWN])
    {
        Controle_paddle(game,KEY_DOWN);
    }
    if (keystate[SDLK_UP])
    {
        Controle_paddle(game,KEY_UP);
    }

    switch(game->state)
    {
    case PLAYING:
        if (IsGameOver(game) != NO_GAMEOVER)
        {
            game->state = END;
        }
        View_Score(game);
        Controle_ball(game);
        View_SeparationLine(game);
        View_paddle(game);
        View_ball(game);

        break;
    case STARTING:
        View_WelcomeText(game);
        if (keystate[SDLK_SPACE])
            game->state = PLAYING;
        break;

    case END:
        if (keystate[SDLK_SPACE])
        {
            game->state = PLAYING;
            SDL_Delay(600);
        }
        View_GameOver(game);

        break;
    default:
        break;


    }
    return 0;
}


