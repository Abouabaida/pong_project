#include "server_udp.h"
#include "network.h"
#include "list.h"
#include "time.h"
#include "sys/time.h"
#include "view.h"
struct sockaddr_in clients_addresses[MAX_PLAYERS];
int number_of_connected_clients = 0;

void prepare_server(int *sock, struct sockaddr_in *server_sock) {
    memset(clients_addresses, 0, sizeof(struct sockaddr_in) * MAX_PLAYERS);
    if ((*sock = socket(PF_INET, SOCK_DGRAM, IPPROTO_UDP)) < 0) {
        perror("socket failed");
    }
    if (bind(*sock, (struct sockaddr*) server_sock, sizeof(struct sockaddr)) < 0) {
        perror("bind server error");
    }
}

struct sockaddr_in receive_data(int sock, int16_t data[]) {
    struct sockaddr_in addr;
    socklen_t addr_size = sizeof(struct sockaddr);
    recvfrom(sock, data, sizeof(int16_t) * 4, 0, (struct sockaddr*)&addr, &addr_size);
    return addr;
}

void send_data(int sock, struct sockaddr_in client, int16_t data[], int size) {
    socklen_t addr_size = sizeof(struct sockaddr);
    sendto(sock, data, sizeof(int16_t) * size, 0, (struct sockaddr*)&client, addr_size);
}

void* server_receive_loop(void *arg) {
    int socket = *((int *) arg);
    int client_pos = 0;
    struct sockaddr_in client_addr;
    int16_t tab[4];
    while (1) {
        client_addr = receive_data(socket, tab);
        client_pos = addr_pos_in_tab(client_addr, clients_addresses, number_of_connected_clients);
        if (its_an_old_client(client_pos)) {
            printf("SERVER : RECEIVING data = %d\n",tab[1]);
            Move_Paddle(tab[1],tab[0]);
        }
        if (tab[0] == -1 && client_pos < MAX_PLAYERS) {
            add_adr_to_list(client_pos, &client_addr);
            int16_t tab[3];
            tab[0] = -1;
            tab[1] = client_pos;
            send_data(socket, clients_addresses[client_pos], tab, 3);
        }
        usleep(50);
    }
}

void server_send_client(int socket, int16_t id, int16_t keys,game_t *game) {
    int16_t tab[8];
   // while (1) 
    {
        int i;
        for (i = 1; i < number_of_connected_clients; i++) {
                tab[0] = 1;
                tab[1] = keys;
                tab[2] = game->ball.x;
                tab[3] = game->ball.y;
                tab[4] = game->ball.w;
                tab[5] = game->ball.h;
                tab[6] = game->score[0];
                tab[7] = game->score[1];
                printf("SERVER : SENDING data to %d:%d:%d:%d:%d:%d:%d:%d\n",tab[0],tab[1],tab[2],tab[3],tab[4],tab[5],tab[6],tab[7]);
                send_data(socket, clients_addresses[i], tab, 8);
                usleep(20);
            //send_data(socket, clients_addresses[i], bullet_array, 1 + (bullets_n * 2));
        }
    }
}

int its_an_old_client(int client_pos) {
    return (client_pos < number_of_connected_clients && client_pos >= 0);
}

void add_adr_to_list(int client_pos, struct sockaddr_in *client_addr) {
    if (client_pos >= number_of_connected_clients) {
        clients_addresses[number_of_connected_clients++] = *client_addr;
    }
}
