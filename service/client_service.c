#include <stdio.h>
#include <stddef.h>

#include "client_service.h"
#include "../repo/client_repository.h"


void create_client(Client *client){
    printf("Create client\n");
    save_client(client);
}

void get_client_by_document(const char *document, Client *client) {

    printf("Get client by document: %s\n", document);
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