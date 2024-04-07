#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Enums
enum AccountType { DEBIT, CHECKING };
enum TransactionType { DEPOSIT, WITHDRAWAL, TRANSFER };

// Definición de estructuras
typedef struct {
    int id;
    char full_name[100];
    char document[30];
    char address[100];
    char phone_number[20];

    //puntero
    struct Account *accounts; //account's list
} Client;

typedef struct {
    int id;
    char account_number[20];
    enum AccountType account_type;
    double balance;
    int client_id;  

    //puntero
    struct Transaction *transactions; //list of transactions
    struct Transfer *transfers; // list of transfers
} Account;

typedef struct {
    int id;
    double amount;
    time_t date_time;
    int origin_account;
    int destination_account;
} Transfer;

typedef struct {
    int id;
    enum TransactionType transaction_type;
    double amount;
    time_t date_time;
    int account_id;
    int transfer_id;

    //pointer to transfer
    struct Transfer *transfer;
} Transaction;


int main(){
    printf("hola mudnos");

    
    return 0;
}