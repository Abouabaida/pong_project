#include "view.h"

int View_MainWindow(game_t *game)
{

	SDL_Init(SDL_INIT_VIDEO);


	SDL_WM_SetCaption("Pong Game", "jeu");

	game->screen = SDL_SetVideoMode(720, 720, 32, SDL_DOUBLEBUF);
	if (game->screen == NULL) {
		printf("Error : %s\n", SDL_GetError());
		return 1;
	}
	return 0;
}
int View_Init(game_t *game){
    View_MainWindow(game);
    return 0;
}

 void View_background(game_t *game)
{
    SDL_Rect src;

    src.x = 0;
    src.y = 0;
    src.w = game->screen->w;
    src.h = game->screen->h;

    SDL_FillRect(game->screen,&src,0);

}

 void View_ball(game_t *game)
{

    SDL_Rect src;

    src.x = game->ball.x;
    src.y = game->ball.y;
    src.w = game->ball.w;
    src.h = game->ball.h;

    if (!SDL_FillRect(game->screen,&src,255))
         printf("View_ball Fail \n");
 }

 void View_paddle(game_t *game)
{

    SDL_Rect src;
    int i;

    for (i = 0; i < 2; i++)
    {
        src.x = game->paddle[i].x;
        src.y = game->paddle[i].y;
        src.w = game->paddle[i].w;
        src.h = game->paddle[i].h;

        if (!SDL_FillRect(game->screen,&src,255))
            printf("View_paddle Fail \n");
    }
}

int View_Update(game_t *game)
{
    SDL_Flip(game->screen);
    SDL_Delay(10);
    return 0;
}
