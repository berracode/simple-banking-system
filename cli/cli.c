#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli.h"
#include "../service/client_service.h"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void options() {
     int i;
    scanf("%d", &i);
    clear_input_buffer();

    switch (i){
        case 1:
            system("clear");
            create_client_cli();
            break;
        case 2:
            system("clear");
            get_all_clients();
            break;
        case 3:
            system("clear");
            get_by_random_index_cli();
            break;
        case 4:
            exit(0);
            break;
        
        default:
            system("clear");
            menu();
    }

}

void menu(){

    printf("1. create client\n");
    printf("2. list all client\n");
    printf("3. get by index\n");
    printf("4. exit\n");
    printf("Enter your option: ");

    options();

}

void commands_init() {

    printf("BANKING SYSTEM FOR YOU BABY ;)\n");
    printf("What do you want to do?\n\n");
    menu();
    
    
}



void create_client_cli(){
    printf("CREATE CLIENT\n");

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

void get_by_random_index_cli(){
    printf("GET A CLIENT BY INDEX\n"); //for example

    int index;
    printf("Ingrese el nombre completo del cliente: ");
    scanf("%d", &index);
    clear_input_buffer();

    get_by_random_index(index);


}