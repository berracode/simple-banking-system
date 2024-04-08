#include <stdio.h>

#include "client_service.h"
#include "../repo/client_repository.h"

void create_client(Client *client){
    printf("client service _ create_client\n");
    printf("Name: %s\n", client->full_name);

    //FINALMENTE GUARDANDO
    save_client(client);
    
}