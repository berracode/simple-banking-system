#ifndef CLIENT_REPOSITORY_H
#define CLIENT_REPOSITORY_H

#include "../domain/client.h"

void save_client(Client *client);
void fetch_all_clients();
void fetch_by_random_index(int index);
void fetch_by_document(const char *document, Client *client);

#endif /* CLIENT_REPOSITORY_H */