#include <stdio.h>
#include <stddef.h>

#include "client_service.h"
#include "../repo/client_repository.h"

void print_client(Client *client){
    printf("\n\tid: %d", client->id);
    printf("\n\tName: %s", client->full_name);
    printf("\n\tdocument: %s", client->document);
    printf("\n\tphone: %s", client->phone_number);
    printf("\n\taddress: %s", client->address);

}

void create_client(Client *client){
    printf("client service _ create_client\n");
    print_client(client);

    printf("Size of Client struct: %zu bytes\n", sizeof(Client));

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