#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <time.h>


#include "cli.h"
#include "../service/client_service.h"
#include "../service/account_service.h"
#include "../service/transfer_service.h"
#include "../service/transaction_service.h"



void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void transfer_money_cli(Client *client){
    // pedirle la cuenta origen al usuario
    // pedirle la cuenta destino
    // cantidad a transferir

    Account origin_account;
    Account destination_account;
    double amount_to_transfer = 0;
    printf("Enter the origin account: ");
    scanf("%s", origin_account.account_number);

    printf("Enter the destination account: ");
    scanf("%s", destination_account.account_number);

    if (strcmp(origin_account.account_number , destination_account.account_number)==0){
        printf("Origin and destination account could not be equals\n");
        return;
    }

    printf("Amount to transfer: ");
    scanf("%lf", &amount_to_transfer);

    // buscar en la bd, la cuenta origen y cuenta destino para saber que existen (poner en marcha el position_seek) capa service
    // validar que el moton a transferir es menor o igual que el monto de la cuenta origen

    get_by_account_number(origin_account.account_number,&origin_account);
    if(client->id != origin_account.client_id){
        printf("Account does not belong to the user\n");
        return;
    }
    get_by_account_number(destination_account.account_number,&destination_account);

    if (origin_account.balance < amount_to_transfer){
        printf("Insufficient balance\n");
        return;
    }

    // si el moto es <= cuenta_origen.amount entonces ingresar
    // una transferencia en la BD transferencia.

    Transfer new_transfer;
    new_transfer.amount = amount_to_transfer;
    new_transfer.destination_account = destination_account.id;
    new_transfer.origin_account = origin_account.id;

    create_transfer(&new_transfer);


    // LUEGO registrarla como una transaccion (id, tipo transferencia, monto, cuenta id es cuenta origen)
    Transaction origin_transaction;
    origin_transaction.amount = amount_to_transfer;
    origin_transaction.account_id = origin_account.id;
    origin_transaction.transfer_id = new_transfer.id;
    origin_transaction.transaction_type = TRANSFER;
    create_transaction(&origin_transaction);

    Transaction destination_transaction;
    destination_transaction.amount = amount_to_transfer;
    destination_transaction.account_id = destination_account.id;
    destination_transaction.transfer_id = new_transfer.id;
    destination_transaction.transaction_type = TRANSFER;
    create_transaction(&destination_transaction);


    // restar el dinero de la cuenta origen
    double new_balance = origin_account.balance - amount_to_transfer;
    printf("New balance origin account: %lf\n", new_balance);
    update_balance(origin_account.id, new_balance, &origin_account);

    // sumar el dinero a la cuenta destino (usar position seek para busquedas rapidas)
    new_balance = destination_account.balance + amount_to_transfer;
    printf("New balance destination account: %lf\n", new_balance);
    update_balance(destination_account.id, new_balance, &destination_account);
}

void banking_transactions(Client *client) {
    // preguntarle de que cuenta quiere las transacciones
    Account account_to_find;
    printf("Enter the account: ");
    scanf("%s", account_to_find.account_number);
    // validar si la cuenta es existe y si es de él
    get_by_account_number(account_to_find.account_number,&account_to_find);
    if(client->id != account_to_find.client_id){
        printf("Account does not belong to the user\n");
        return;
    }
    // con el ID de la CUENTA, buscar transacciones por id cuenta
    get_by_account_id(account_to_find.id);
    //mostrar todas las transacciones de la siguiente forma: 
    // id transaccion | tipo transaccion | cuenta | fecha |
    // TODO: hacer consultas cruzada para dar el detalle de la transferencia (IMPLEMENTAR LISTA LIGADA)


}

void options_client(Client *client) {

    int i;
    scanf("%d", &i);
    clear_input_buffer();

    switch (i){
        case 1:
            system("clear");
            printf("DEPOSIT MONEY\n");
            break;
        case 2:
            system("clear");
            printf("withdrawals\n");
            break;
        case 3:
            system("clear");
            printf("TRANSFER\n");
            transfer_money_cli(client);
            break;
        case 4:
            system("clear");
            printf("BALANCE\n");
            break;
        case 5:
            system("clear");
            printf("LIST MY ACCOUNTS\n");
            break;
        case 6:
            system("clear");
            printf("BANKING TRANSACTIONS\n");
            banking_transactions(client);
            break;
        case 99:
            exit(0);
            break;
        default:
            system("clear");
            menu();
    }
}

void menu_client(Client *client){

    system("clear");
	printf("\n\tWelcome %s\n",client->full_name);

    printf("1. Deposit money\n");
    printf("2. withdrawals\n");
    printf("3. transfer\n");
    printf("4. balance\n");
    printf("5. list my accounts\n");
    printf("6. banking transactions\n");
    printf("99. exit\n");
    printf("Enter your option: ");

    options_client(client);

}

void login(){
    //user ingresa su documento y su password. 
    //se busca si el usuario con documento existe
    //se compara si la password == a la ingresada por el user.
    //si sí, muestra el menu para realizar deposito, retiro, o transferencia
    //sino, le muestra usuario o contraseña incorrecta, volver a intentarlo, salir o volver al menu anterior
    Client client;
    char *document_to_find = malloc(30*sizeof(char));
    char *password_entered = malloc(10*sizeof(char));
    printf("Enter your document: ");
    scanf("%s", document_to_find);

    printf("Enter your password: ");
    scanf("%s", password_entered);

    get_client_by_document(document_to_find, &client);

    if(client.id == -1 && strcmp(document_to_find, client.document) != 0) {
        printf("Client not found\n");
    } else {
        printf("Client exist\n");
        if(strcmp(password_entered, client.password) == 0){
            printf("Client exist and password is correct\n");
            menu_client(&client);

        } else {
            printf("Incorrect password\n");
        }

    }

}

void options() {
    int i;
    int id_client = 0;
    scanf("%d", &i);
    clear_input_buffer();

    switch (i){
        case 1:
            system("clear");
            printf("LOG IN\n");
            login();
            break;
        case 11:
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

    printf("1. Login to your account \n");
    printf("11. create client\n");
    printf("2. list all client\n");
    printf("3. get by index\n");
    printf("4. Register an account?\n");
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
    Client client;
    char exits = 0;
    int id_client = 0;
    do
    {
        system("clear");
        printf("REGISTER AN ACCOUNT\n");

        // pregutar si el cliente ya existe.
        printf("1. Client exist.\n");
        printf("2. Client does not exist\n");
        printf("Ingrese su opción: ");
        scanf("%c", &exits);
        clear_input_buffer();
        if(exits == '1') {
            printf("Enter document's client: \n");
            scanf("%s", client.document);
            get_client_by_document(client.document, &client);
            if(client.id == -1){
                printf("Client not found\n");
                return;
            }
            id_client = client.id;
        } else {
            create_client_cli(&id_client);
        }
    } while (exits != '1' && exits != '2');

    printf("Enter account number: ");
    scanf("%s", account.account_number);

    printf("Account type (0 for savings, 1 for checking): ");
    int account_type_input;
    scanf("%d", &account_type_input);
    account.account_type = account_type_input == 0 ? SAVINGS : CHECKING;

    printf("Enter balance: ");
    scanf("%lf", &account.balance);

    account.client_id = id_client;

    create_account(&account);

}

void create_client_cli(int *id_client){
    printf("CREATE CLIENT\n");

    Client new_client;

    printf("Enter your full name: ");
    fgets(new_client.full_name, sizeof(new_client.full_name), stdin);
    strtok(new_client.full_name, "\n"); // for delete the enter in the end

    printf("Enter your document: ");
    fgets(new_client.document, sizeof(new_client.document), stdin);
    strtok(new_client.document, "\n");

    printf("Enter your address: ");
    fgets(new_client.address, sizeof(new_client.address), stdin);
    strtok(new_client.address, "\n");

    printf("Enter your phone number: ");
    fgets(new_client.phone_number, sizeof(new_client.phone_number), stdin);
    strtok(new_client.phone_number, "\n");

    printf("Enter your password: ");
    fgets(new_client.password, sizeof(new_client.password), stdin);
    strtok(new_client.password, "\n");

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