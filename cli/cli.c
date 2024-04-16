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
#include "../service/print_presenter_service.h"



void clear_input_buffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

void check_balance(Client *client){
    //cuenta de la cual se desea conocer el balance
    // validar que pertenezca al usuario
    // obtener balance

    Account account;
    printf("Enter the account: ");
    scanf("%s", account.account_number);

    get_by_account_number(account.account_number, &account);
    if(client->id != account.client_id){
        printf("Account does not belong to the user\n");
        return;
    }

    printf("Account balance: %lf\n", account.balance);


}


void withdrawals_cli(Client *client) {
    //cuenta en la cual retirar el dinero
    //validar que la cuenta pertenece al usuario
    // actaulizar balance.
    Account origin_account;
    double amount_to_withdraw = 0;
    printf("Enter the amount to withdraw: ");
    scanf("%s", origin_account.account_number);

    printf("Amount: ");
    scanf("%lf", &amount_to_withdraw);

    if (amount_to_withdraw <= 0){
        printf("Amout must be greater than zero\n");
        return;
    }

    get_by_account_number(origin_account.account_number, &origin_account);
    if(client->id != origin_account.client_id){
        printf("Account does not belong to the user\n");
        return;
    }

    if(origin_account.balance < amount_to_withdraw){
        printf("Insuficient balance\n");
        return;
    }

    Transaction origin_transaction;
    origin_transaction.amount = amount_to_withdraw;
    origin_transaction.account_id = origin_account.id;
    origin_transaction.transfer_id = -1;
    origin_transaction.transaction_type = WITHDRAWAL;
    create_transaction(&origin_transaction);

    // RESTAR el dinero de la cuenta destino
    double new_balance = origin_account.balance - amount_to_withdraw;
    printf("New balance origin account: %lf\n", new_balance);
    update_balance(origin_account.id, new_balance, &origin_account);

}

void deposit_money_cli(Client *client) {
    //cuenta en la cual depositar el dinero
    //validar que la cuenta pertenece al usuario
    // actaulizar balance.
    Account destination_account;
    double amount_to_deposit = 0;
    printf("Enter the destination account: ");
    scanf("%s", destination_account.account_number);

    get_by_account_number(destination_account.account_number, &destination_account);
    if(client->id != destination_account.client_id){
        printf("Account does not belong to the user\n");
        return;
    }

    printf("Amount to deposit: ");
    scanf("%lf", &amount_to_deposit);

    if (amount_to_deposit <= 0){
        printf("Amout can not be zero\n");
        return;
    }


    Transaction destination_transaction;
    destination_transaction.amount = amount_to_deposit;
    destination_transaction.account_id = destination_account.id;
    destination_transaction.transfer_id = -1;
    destination_transaction.transaction_type = DEPOSIT;
    create_transaction(&destination_transaction);

    // SUMAR el dinero de la cuenta destino
    double new_balance = destination_account.balance + amount_to_deposit;
    printf("Actual balance in account: %lf\n", destination_account.balance);
    update_balance(destination_account.id, new_balance, &destination_account);
    printf("New balance in account: %lf\n", destination_account.balance);


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
    print_headers("BANKING TRANSACTIONS");
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
    system("clear");
    print_headers("BANKING TRANSACTIONS");

    // con el ID de la CUENTA, buscar transacciones por id cuenta
    get_by_account_id(account_to_find.id);
    //mostrar todas las transacciones de la siguiente forma: 
    // id transaccion | tipo transaccion | cuenta | fecha |
    // TODO: hacer consultas cruzada para dar el detalle de la transferencia (IMPLEMENTAR LISTA LIGADA)


}

void back_menu_client_options(int *options, Client *client){
    scanf("%d", options);
    clear_input_buffer();
    switch (*options){
    case 1:
        menu_client(client);
        break;
    default:
        exit(0);
        break;
    }

}

void back_menu_client(Client *client){
    int option = 0;
    do{
        printf("--------------------------------------------------\n\n");
        printf("[ 1 ]. Back\n");
        printf("[ 2 ]. exit\n");
        printf("Enter your option: ");

        back_menu_client_options(&option, client);
    } while (option !=1 && option != 2);

}

int options_client(Client *client) {

    int i;
    int incorrect_option = 0;
    scanf("%d", &i);
    clear_input_buffer();

    switch (i){
        case 1:
            system("clear");
            print_headers("DEPOSIT MONEY");
            deposit_money_cli(client);
            break;
        case 2:
            system("clear");
            print_headers("WITHDRAWALS");
            withdrawals_cli(client);
            break;
        case 3:
            system("clear");
            print_headers("TRANSFER");
            transfer_money_cli(client);
            break;
        case 4:
            system("clear");
            print_headers("BALANCE");
            check_balance(client);
            break;
        case 5:
            print_headers("LIST MY ACCOUNTS");
            break;
        case 6:
            system("clear");
            banking_transactions(client);
            break;
        case 7:
            system("clear");
            printf("Log out\n");
            menu();
            break;
        case 99:
            exit(0);
            break;
        default:
            incorrect_option = 1;
            system("clear");
            printf("You have to select a correct option.\n");
    }
    if (incorrect_option != 1){
        back_menu_client(client);
    }
    return i;
}

void menu_client(Client *client){

    int option = 0;
    
    do{
        system("clear");
        printf("\t\t#####  WELCOME DEAR %s  #####\n\n",client->full_name);

        printf("[ 1 ]. Deposit money\n");
        printf("[ 2 ]. Withdrawals\n");
        printf("[ 3 ]. Transfer\n");
        printf("[ 4 ]. Check balance\n");
        printf("[ 5 ]. List my accounts\n");
        printf("[ 6 ]. Banking transactions\n");
        printf("[ 7 ]. Log out\n");
        printf("[ 99]. exit\n");
        printf("Enter your option: ");

        option = options_client(client);
    } while (option != 99 && option != 7);

}

void login(){
    print_headers("LOGIN");

    Client client;
    char document_to_find[30];
    char password_entered[10];
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
    scanf("%d", &i);
    clear_input_buffer();

    switch (i){
        case 1:
            system("clear");
            login();
            break;
        case 2:
            system("clear");
            create_account_cli();
            break;
        case 3:
            system("clear");
            get_all_clients();
            break;
        case 4:
            system("clear");
            get_by_random_index_cli();
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
    printf("\t\t\t\tBANKING SYSTEM \n\n");
    printf("\t\t#####  WELCOME TO THE MAIN MENU BABY  #####\n\n");
    printf("What do you want to do?\n\n");

    printf("[ 1 ]. Login to your account \n");
    printf("[ 2 ]. Register an account?\n");
    printf("[ 3 ]. List all clients\n");
    printf("[ 4 ]. Get client by some ID (only for test)\n");
    printf("[ 5 ]. List all accouts. (only for test)\n");
    printf("[ 99]. exit\n");
    printf("Enter your option: ");

    options();

}

void commands_init() {
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

     // LUEGO registrarla como una transaccion (id, tipo transferencia, monto, cuenta id es cuenta origen)
    Transaction initial_transaction;
    initial_transaction.amount = account.balance;
    initial_transaction.account_id = account.id;
    initial_transaction.transaction_type = DEPOSIT;
    create_transaction(&initial_transaction);

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