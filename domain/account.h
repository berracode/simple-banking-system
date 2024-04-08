#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "transfer.h"
#include "transaction.h"

enum AccountType { DEBIT, CHECKING };

#define RECORD_SIZE 300
typedef struct {
    int id; //4 bytes = 32 bits = 2^32 (10 digits o 10 caracteres en archivo)
    char account_number[20]; 
    enum AccountType account_type;
    double balance;
    int client_id;  

    //puntero
    struct Transaction *transactions; //list of transactions
    struct Transfer *transfers; // list of transfers
} Account;

#endif /*ACCOUNT_H*/

