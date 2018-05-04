#include "view.h"

int Game_Init(game_t *game)
{
    View_Init(game);
    init_ball(game);
    game->state = STARTING;
    game->score[0] = 0;
    game->score[1] = 0;
    return 0;
}

int main( int argc, char * argv[] )
{
    game_t game;
    SDL_Event e;

    Game_Init(&game);

    while (game.state != QUIT)
    {
        SDL_PumpEvents();
        SDL_PollEvent(&e);
        if (e.type == SDL_QUIT)
        {
            break;
        }

        View_background(&game);
        Game_Engine(&game);

        View_Update(&game);
    }

    SDL_Quit();

    return 0;
}
