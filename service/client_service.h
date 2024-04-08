#ifndef CLIENT_SERVICE_H
#define CLIENT_SERVICE_H

#include "../domain/client.h"

void create_client(Client *client);

void get_all_clients();

void get_by_random_index(int index);

#endif
