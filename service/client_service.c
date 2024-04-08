#include <stdio.h>
#include <stddef.h>

#include "client_service.h"
#include "../repo/client_repository.h"

void create_client(Client *client){
    printf("client service _ create_client\n");
    
    printf("id: %d\n", client->id);
    printf("Name: %s\n", client->full_name);
    printf("document: %s\n", client->document);
    printf("phone: %s\n", client->phone_number);
    printf("address: %s\n", client->address);

    printf("id: Tamaño = %zu bytes, Desplazamiento = %zu bytes\n", sizeof(int), offsetof(Client, id));
    printf("full_name: Tamaño = %zu bytes, Desplazamiento = %zu bytes\n", sizeof(char[100]), offsetof(Client, full_name));
    printf("document: Tamaño = %zu bytes, Desplazamiento = %zu bytes\n", sizeof(char[30]), offsetof(Client, document));
    printf("address: Tamaño = %zu bytes, Desplazamiento = %zu bytes\n", sizeof(char[100]), offsetof(Client, address));
    printf("phone_number: Tamaño = %zu bytes, Desplazamiento = %zu bytes\n", sizeof(char[20]), offsetof(Client, phone_number));
    printf("accounts: Tamaño = %zu bytes, Desplazamiento = %zu bytes\n", sizeof(struct Account*), offsetof(Client, accounts));

     printf("Size of Client struct: %zu bytes\n", sizeof(Client));

    //FINALMENTE GUARDANDO
    save_client(client);
    
}

void get_all_clients(){
    //to do

    fetch_all_clients();
}

void get_by_random_index(int index) {

    fetch_by_random_index(index);
}