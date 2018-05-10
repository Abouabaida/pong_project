#ifndef VIEW_H_INCLUDED
#define VIEW_H_INCLUDED

#include "SDL/SDL.h"
#include <SDL_ttf.h>
#include <stdio.h>

#define KEY_DOWN 0
#define KEY_UP 1
#define STARTING 0
#define PLAYING 1
#define END 2
#define QUIT 2
#define PLAYER_1_WIN 1
#define PLAYER_2_WIN 2
#define NO_GAMEOVER 3

#define FALSE 0
#define TRUE 1

#define CLIENT 0
#define SERVER 1
#define UNKNOWN 2 

#define MAX_PLAYERS 10
#define BUF_MAX 256
#define FRAME_TIME 16666

#define ONE_PLAYER_MODE 0
#define TWO_PLAYER_MODE 1
#define SERVER_MODE 2
#define CLIENT_MODE 3

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
   int state;
   int type;
   int mode;
   TTF_Font *font;
} game_t;

void View_ball(game_t *game);
void View_paddle(game_t *game);
void View_Score(game_t *game);
int View_MainWindow(game_t *game);
void ask_for_ip(game_t *game, char *ip);
void server_or_client(game_t *game);
void View_GameOver(game_t *game);
int View_Update(game_t *game);
void View_background(game_t *game);
int View_Init(game_t *game);
void init_ball(game_t *game);
void View_SeparationLine(game_t *game);

int Move_Paddle(int16_t keystate, int UserId);
void View_WelcomeText(game_t *game);

void Shutdown();
void server_send_client(int socket, int16_t id, int16_t keys,game_t *game);
void Controle_ball(game_t *game);
int check_collision(ball_t a, paddle_t b);
int IsGameOver(game_t *game);
void Controle_paddle(game_t *game,int key_pressed,int UserId);
void move_paddle_enemy(game_t *game);
int get_Action(Uint8 *keystate,int16_t *my_id,int mode );
#endif // VIEW_H_INCLUDED
