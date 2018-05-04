#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include "SDL/SDL.h"
#include <SDL_ttf.h>

#define KEY_DOWN 0
#define KEY_UP 1
#define STARTING 0
#define PLAYING 1
#define END 2
#define QUIT 2

#define PLAYER_1_WIN 1
#define PLAYER_2_WIN 2
#define NO_GAMEOVER 3

typedef struct ball_s
{
    int x;
    int y;
    int w;
    int h;
    int dx;
    int dy;
} ball_t;

typedef struct paddle
{
    int x;
    int y;
    int w;
    int h;
} paddle_t;

typedef struct game
{
    ball_t ball;
    paddle_t paddle[2];
    int score[2];
    SDL_Surface *screen;
    SDL_Surface *title;
    int state;
} game_t;



void Controle_paddle(game_t *game,int d);
void move_paddle_ai(game_t *game);
void Controle_ball(game_t *game);
int check_collision(ball_t a, paddle_t b);
int Game_Engine(game_t *game);
int View_MainWindow(game_t *game);
int View_Init(game_t *game);
void View_background(game_t *game);
void View_ball(game_t *game);
void View_net(game_t *game);
void View_paddle(game_t *game);
int View_Update(game_t *game);
void init_ball(game_t *game);
void View_WelcomeText(game_t *game) ;
void View_GameOver(game_t *game);
int IsGameOver(game_t *game);
void View_Score(game_t *game);
void View_SeparationLine(game_t *game);
#endif // VIEW_H_INCLUDED
