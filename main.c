#include <stdio.h>
#include "view.h"
#include "client_udp.h"
#include "server_udp.h"
#include "network.h"
#include <pthread.h>
#include <stdint.h>

game_t game;
int16_t my_id = -1;
int SpaceIsPressed = FALSE;

void receive_new_id(int id) {
   my_id = id;
   printf("my_id is now: %d\n", my_id);
}

void* client_loop(void *arg) {
   int socket = *((int *) arg);
   int16_t tab[BUF_MAX];
   int id;
   while (1) {
      client_listen(socket, tab);
      id = tab[0];
      printf("%d RECEIVING %d\n",tab[0],tab[1]);
      if (id == -1) {
         receive_new_id(tab[1]);
      }
      if (id == 1) {
         Move_Paddle(tab[1],0);
         game.ball.x = tab[2];
         game.ball.y = tab[3];
         game.ball.w = tab[4];
         game.ball.h = tab[5];
         game.score[0] = tab[6];
         game.score[1] = tab[7];
         printf("SERVER : RECEIVING data %d:%d:%d:%d:%d:%d:%d:%d\n",tab[0],tab[1],tab[2],tab[3],tab[4],tab[5],tab[6],tab[7]);
      }
      usleep(50);
   }
}
int Game_Init(game_t *game)
{
   View_Init(game);
   init_ball(game);
   game->state = STARTING;
   game->score[0] = 0;
   game->score[1] = 0;
   return 0;
}
int Move_Paddle(int16_t keystate, int UserId){
   if(keystate == -1 )
      return 0;
   if(UserId == 0){
      Controle_paddle(&game,keystate,UserId);
   } else {
      Controle_paddle(&game,keystate,UserId);
   }
   return FALSE;
}
void Shutdown(){
   SDL_Quit();
   exit(1);
}
int main(){
   struct sockaddr_in server_addr, client_addr;
   int sock_server, sock_client;
   char *server_ip_addr = NULL;
   pthread_t thread_id_server, thread_id_client;
   Game_Init(&game);
   server_or_client(&game);
   if (game.type == CLIENT) {
      server_ip_addr = malloc(16 * sizeof(char));
      ask_for_ip(&game,server_ip_addr);
   }
   if((game.mode == SERVER_MODE) || (game.mode == CLIENT_MODE)) {
      server_addr = server_sock_addr(server_ip_addr);
      client_addr = client_sock_addr();
      if (game.type == SERVER) 
      {
         prepare_server(&sock_server, &server_addr);
         pthread_create(&thread_id_server, NULL, server_receive_loop, &sock_server);
      }
      prepare_client(&sock_client, &client_addr);
      pthread_create(&thread_id_client, NULL, client_loop, &sock_client);
      while (my_id < 0) {
         send_to_server(sock_client, server_addr, my_id, 0);
         usleep(100);
      }
   }
   if(game.mode == ONE_PLAYER_MODE)
      my_id = 1;
   SDL_Event e;

   while (1) {
      View_background(&game);
      SDL_PumpEvents();
      if (SDL_PollEvent(&e)) {
         if (e.type == SDL_QUIT) {
            Shutdown();
         }
      }
      if(game.state == END)
      {
         View_GameOver(&game);
         View_Update(&game);
         sleep(10);
         break;
      }
      if(game.state == STARTING)
      {
         if (e.type == SDL_KEYDOWN) {
            if (e.key.keysym.sym == SDLK_SPACE)
               SpaceIsPressed = TRUE;
         }
         if (IsGameOver(&game) != NO_GAMEOVER)
            game.state = END;
         if(SpaceIsPressed == TRUE)
            Controle_ball(&game);
         else
            View_WelcomeText(&game);
         View_Score(&game);
         if(game.mode == ONE_PLAYER_MODE)
            move_paddle_enemy(&game);
         View_SeparationLine(&game);
         View_paddle(&game);
         View_ball(&game);
      }
      Uint8 *keystate = SDL_GetKeyState(NULL);
      int16_t key = get_Action(keystate,&my_id,game.mode); 
      Move_Paddle(key,my_id);

      if((game.type == CLIENT) && (key != -1))
         send_to_server(sock_client, server_addr, my_id, key);
      if((game.type == SERVER) && (key != -1))
         server_send_client(sock_server, my_id, key,&game);
      usleep(30);
      View_Update(&game);
   }

   if((game.mode == SERVER_MODE) || (game.mode == CLIENT_MODE)) {
      close(sock_client);
      close(sock_server);
      pthread_cancel(thread_id_client);
      pthread_cancel(thread_id_server);
   }
   SDL_Quit();
   return 0;
}
