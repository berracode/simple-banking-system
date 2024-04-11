#include <stdio.h>
#include <stddef.h>

#include "client_service.h"
#include "../repo/client_repository.h"

void create_client(Client *client){
    printf("client service _ create_client\n");
    
    printf("Name: %s\n", client->full_name);
    printf("document: %s\n", client->document);
    printf("phone: %s\n", client->phone_number);
    printf("address: %s\n", client->address);

    printf("Size of Client struct: %zu bytes\n", sizeof(Client));

    //FINALMENTE GUARDANDO
    save_client(client);
}

void get_client_by_document(const char *document, Client *client) {

    printf("document: %s\n", document);

    // Verificar si document es NULL
    if (document == NULL) {
        perror("Document is NULL\n");
        return;
    }

    if(document[0] == '0') {
        perror("Invalid document\n");
        return;
    }

    fetch_by_document(document, client);

}


void get_all_clients(){
    //to do

    fetch_all_clients();
}

void get_by_random_index(int index) {

    fetch_by_random_index(index);
}