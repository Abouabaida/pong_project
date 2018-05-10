#include "view.h"
#include <unistd.h>

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

   game->screen = SDL_SetVideoMode(720, 720, 32, SDL_DOUBLEBUF|SDL_HWSURFACE);
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

void ask_for_ip(game_t *game, char *ip) {

   SDL_Event e;
   int position = 0;
   int ok = FALSE;
   SDL_Rect rect;

   rect.x = 0;
   rect.y = 50;
   rect.w = 100;
   rect.h = 100;
   memset(ip, ' ', 15*sizeof(char));
   while (!ok) {
      View_background(game);
      if (SDL_PollEvent(&e))
      {
         if (e.type == SDL_QUIT)
         {
            break;
         }
         if (e.type == SDL_KEYDOWN)
         {
            if ((e.key.keysym.sym >= SDLK_0 && e.key.keysym.sym <= SDLK_9) || e.key.keysym.sym == SDLK_PERIOD) {
               if (position > 14) {
                  position = 14;
               }
               ip[position] = e.key.keysym.sym;
               position++;
            }
            if (e.key.keysym.sym == SDLK_BACKSPACE) {
               position--;
               if (position < 0) {
                  position = 0;
               }
               ip[position] = ' ';
            }
            if (e.key.keysym.sym == SDLK_RETURN) {
               ip[position] = 0;
               ok = TRUE;
            }
         }
      }
      usleep(200);
      SDL_Color text_color = {255, 0, 0};
      SDL_Surface  *GameOver = TTF_RenderText_Solid(game->font, "Please enter your ip address",   text_color);
      SDL_Surface  *GameOver2 = TTF_RenderText_Solid(game->font, ip,   text_color);
      SDL_BlitSurface(GameOver, NULL, game->screen, NULL);
      SDL_BlitSurface(GameOver2, NULL, game->screen, &rect);
      View_Update(game);
   }
}
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
void server_or_client(game_t *game){
   SDL_Event e;
   int pressed = FALSE;
   while (!pressed) {
      View_background(game);
      if (SDL_PollEvent(&e)) {

         if (e.type == SDL_QUIT) {
            Shutdown();
         }
         if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_4) {
               game->mode = CLIENT_MODE;
               game->type = CLIENT;
               pressed = TRUE;
            } else if (e.key.keysym.sym == SDLK_3) {
               game->mode = SERVER_MODE;
               game->type = SERVER;
               pressed = TRUE;
            }
            else if (e.key.keysym.sym == SDLK_1) {
               game->mode = ONE_PLAYER_MODE;
               game->type = UNKNOWN;
               pressed = TRUE;
            } else if (e.key.keysym.sym == SDLK_2) {
               game->mode = TWO_PLAYER_MODE;
               game->type = UNKNOWN;
               pressed = TRUE;
            }
         }
      }
      SDL_Rect rect;
      SDL_Rect rect1;
      SDL_Rect rect2;
      SDL_Rect rect3;

      rect.x = 0;rect.y = 50; rect.w = 100;rect.h = 100;
      rect1.x = 0;rect1.y = 100; rect1.w = 100;rect1.h = 100;
      rect2.x = 0;rect2.y = 150; rect2.w = 100;rect2.h = 100;
      rect3.x = 0;rect3.y = 200; rect3.w = 100;rect3.h = 100;

      usleep(200);
      SDL_Color text_color = {255, 0, 0};
      SDL_Surface  *GameOver = TTF_RenderText_Solid(game->font, "Press the number " ,   text_color);
      SDL_Surface  *GameOver1 = TTF_RenderText_Solid(game->font, "     Local mode   *1* : Single Player " ,   text_color);
      SDL_Surface  *GameOver2 = TTF_RenderText_Solid(game->font, "     Local mode   *2* : Two Player " ,   text_color);
      SDL_Surface  *GameOver3 = TTF_RenderText_Solid(game->font, "     Network mode *3* : 1st Player (Please use UP DOWN keys) " ,   text_color);
      SDL_Surface  *GameOver4 = TTF_RenderText_Solid(game->font, "     Network mode *4* : 2nd Player (Please use e, d keys) " ,   text_color);
      SDL_BlitSurface(GameOver, NULL, game->screen, NULL);
      SDL_BlitSurface(GameOver1, NULL, game->screen,&rect);
      SDL_BlitSurface(GameOver2, NULL, game->screen,&rect1);
      SDL_BlitSurface(GameOver3, NULL, game->screen,&rect2);
      SDL_BlitSurface(GameOver4, NULL, game->screen,&rect3);
      View_Update(game);
   }
}
void View_GameOver(game_t *game)
{

   SDL_Surface  *GameOver;
   game->font = TTF_OpenFont("FreeSans.ttf", 24);
   if (game->font == NULL)
   {

      TTF_Quit();
      SDL_Quit();
      exit(1);
   }

   SDL_Color text_color = {255, 255, 255};
   GameOver = TTF_RenderText_Solid(game->font, "Player win the game",   text_color);

   SDL_BlitSurface(GameOver, NULL, game->screen, NULL);
}
void View_WelcomeText(game_t *game)
{
   SDL_Rect rect;

   rect.x = 40;
   rect.y = game->screen->h / 2;
   rect.w = 0;
   rect.h = 0;

   SDL_Color text_color = {255, 255, 255};
   SDL_Surface *title = TTF_RenderText_Solid(game->font, "Welcome to Pong game : Press space bar to start playing",   text_color);

   if (title == NULL)
   {

      TTF_Quit();
      SDL_Quit();
      exit(1);
   }
   SDL_BlitSurface(title, NULL, game->screen, &rect);
}

int View_Init(game_t *game)
{
   View_MainWindow(game);
   // Load a font
   game->font = TTF_OpenFont("FreeSans.ttf", 24);
   if (game->font == NULL)
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

   if (SDL_FillRect(game->screen,&src,255) != 0)
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

      if (SDL_FillRect(game->screen,&src,255) != 0)
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

   char Score[20];
   SDL_Surface *Temp;

   SDL_Color text_color = {255, 255, 255};
   snprintf(Score,20,"Score  %d|%d",game->score[0],game->score[1]);
   Temp = TTF_RenderText_Solid(game->font, Score,   text_color);


   SDL_BlitSurface(Temp, NULL, game->screen, NULL);
}
