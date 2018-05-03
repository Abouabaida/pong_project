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
    case STARTING:
        if (keystate[SDLK_SPACE])
            game->state = PLAYING;

        break;
    case PLAYING:

        Controle_ball(game);
        View_paddle(game);
        View_ball(game);

        break;
    case END:
        if (keystate[SDLK_SPACE])
        {
            game->state = 0;
             SDL_Delay(600);
        }

        break;
    default:
        break;


    }
    return 0;
}


