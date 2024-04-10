#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>

#include "cli.h"
#include "../service/client_service.h"
#include "../service/account_service.h"

void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void options() {
    int i;
    int id_client = 0;
    scanf("%d", &i);
    clear_input_buffer();

    switch (i){
        case 1:
            system("clear");
            create_client_cli(&id_client);
            printf("CLIENTE CREADO CON EXITO: %d\n", id_client);
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
            system("clear");
            create_account_cli();
            break;
        case 5:
            system("clear");
            get_all_accounts();
            break;
        case 99:
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
    printf("4. create accout\n");
    printf("5. list all accouts\n");
    printf("99. exit\n");
    printf("Enter your option: ");

    options();

}

void commands_init() {

    printf("BANKING SYSTEM FOR YOU BABY ;)\n");
    printf("What do you want to do?\n\n");
    menu();
}



void create_account_cli(){
    Account account;
    char exits = 0;
    int id_client = 0;
    char *document = malloc(30*sizeof(char));
    do
    {
        system("clear");
        printf("CREATE ACCOUNT\n");

        // pregutar si el cliente ya existe.
        printf("1. Cliente existe.\n");
        printf("2. Cliente no existe.\n");
        printf("Ingrese su opción: ");
        scanf("%c", &exits);
        printf("exist: %c\n", exits);
        clear_input_buffer();
        if(exits == '1') {
            printf("Sí\n");
            printf("Ingrese documento del cliente: ");
            scanf("%s", document);
            
            get_client_by_document(document, &id_client);
            if(id_client == -1){
                printf("Client not found\n");
                free(document);
                return;
            }
            free(document);
        } else {
            //crear cliente
            printf("No\n");
            create_client_cli(&id_client);
        }
    } while (exits != '1' && exits != '2');

    printf("Ingrese el número de cuenta: ");
    scanf("%s", account.account_number);

    printf("Ingrese el tipo de cuenta (0 para ahorros, 1 para corriente): ");
    int account_type_input;
    scanf("%d", &account_type_input);
    account.account_type = account_type_input == 0 ? DEBIT : CHECKING;

    printf("Ingrese el balance de la cuenta: ");
    scanf("%lf", &account.balance);

    account.client_id = id_client;

    create_account(&account);

}

void create_client_cli(int *id_client){
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

    create_client(&new_client);
    *id_client = new_client.id;

}

void get_by_random_index_cli(){
    printf("GET A CLIENT BY INDEX\n"); //for example

    int index;
    printf("Ingrese el nombre completo del cliente: ");
    scanf("%d", &index);
    clear_input_buffer();

    get_by_random_index(index);


}