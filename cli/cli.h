#ifndef CLI_H
#define CLI_H

#include "../domain/client.h"

void clear_input_buffer();
void menu();
void options();
void create_client_cli(int *id_client);
void get_by_random_index_cli();
void create_account_cli();
void menu_client(Client *client);
void commands_init();

#endif