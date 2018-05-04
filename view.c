#include "view.h"

void View_SeparationLine(game_t *game)
{

    SDL_Rect line;

    line.x = game->screen->w / 2;
    line.y = 20;
    line.w = 5;
    line.h = 15;

    //draw the net
    int i,r;

    for(i = 0; i < 25; i++)
    {

        r = SDL_FillRect(game->screen,&line,255);

        if (r != 0)
        {

            printf("fill rectangle faliled in func draw_background()");
        }

        line.y = line.y + 30;
    }

}

int View_MainWindow(game_t *game)
{

    SDL_Init(SDL_INIT_VIDEO);


    SDL_WM_SetCaption("Pong Game", "jeu");

    game->screen = SDL_SetVideoMode(720, 720, 32, SDL_DOUBLEBUF);
    if (game->screen == NULL)
    {
        printf("Error : %s\n", SDL_GetError());
        return 1;
    }

    // Initialize SDL_ttf library
    if (TTF_Init() != 0)
    {

        SDL_Quit();
        exit(1);
    }
    return 0;
}

void View_GameOver(game_t *game)
{
    TTF_Font *font;
    SDL_Surface  *GameOver;
    font = TTF_OpenFont("FreeSans.ttf", 24);
    if (font == NULL)
    {

        TTF_Quit();
        SDL_Quit();
        exit(1);
    }

    SDL_Color text_color = {255, 255, 255};
    GameOver = TTF_RenderText_Solid(font, "PLayer Win the game",   text_color);

    SDL_BlitSurface(GameOver, NULL, game->screen, NULL);
}
void View_WelcomeText(game_t *game)
{
    SDL_BlitSurface(game->title, NULL, game->screen, NULL);
}

int View_Init(game_t *game)
{
    View_MainWindow(game);
    // Load a font
    TTF_Font *font;
    font = TTF_OpenFont("FreeSans.ttf", 24);
    if (font == NULL)
    {

        TTF_Quit();
        SDL_Quit();
        exit(1);
    }

    SDL_Color text_color = {255, 255, 255};
    game->title = TTF_RenderText_Solid(font, "Welecome to Pong game : Press space bar to start playing",   text_color);

    if (game->title == NULL)
    {

        TTF_Quit();
        SDL_Quit();
        exit(1);
    }


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


void View_Score(game_t *game)
{
    TTF_Font *font;
    char Score[20];
    SDL_Surface *Temp;
    font = TTF_OpenFont("FreeSans.ttf", 24);
    if (font == NULL)
    {

        TTF_Quit();
        SDL_Quit();
        exit(1);
    }

    SDL_Color text_color = {255, 255, 255};
    snprintf(Score,20,"Score  %d|%d",game->score[0],game->score[1]);
    Temp = TTF_RenderText_Solid(font, Score,   text_color);


    SDL_BlitSurface(Temp, NULL, game->screen, NULL);
}
