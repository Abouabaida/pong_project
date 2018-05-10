build: main.c	client_udp.c server_udp.c network.c list.c  view.c controle.c
	gcc -o pong main.c client_udp.c server_udp.c network.c list.c view.c controle.c `sdl-config --cflags --libs` -g -lSDL -lSDL_ttf -lpthread -I. -Wall

