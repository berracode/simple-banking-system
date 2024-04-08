#include <stdio.h>
#include <string.h>

#include "cli.h"
#include "../service/client_service.h"

void create_client_cli(){
    printf("Starting...\n");

    Client new_client;

    printf("Ingrese el nombre completo del cliente: ");
    fgets(new_client.full_name, sizeof(new_client.full_name), stdin);
    strtok(new_client.full_name, "\n"); // for delete the enter in the end

    printf("Ingrese el documento del cliente: ");
    fgets(new_client.document, sizeof(new_client.document), stdin);
    strtok(new_client.document, "\n");

    printf("Ingrese la dirección del cliente: ");
    fgets(new_client.address, sizeof(new_client.address), stdin);
    strtok(new_client.address, "\n");

    printf("Ingrese el número de teléfono del cliente: ");
    fgets(new_client.phone_number, sizeof(new_client.phone_number), stdin);
    strtok(new_client.phone_number, "\n");

    new_client.id = 1; // I must think how to increase this ID
    create_client(&new_client);

}