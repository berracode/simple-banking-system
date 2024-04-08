#include <stdio.h>

#include "../repo/client_repository.h"

void save_client(Client *client){
    printf("llamando adaptador secundario (que implementa puerto secundario o de salida)");
    printf("phone: %s\n", client->phone_number);

}


