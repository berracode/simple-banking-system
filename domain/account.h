#ifndef ACCOUNT_H
#define ACCOUNT_H

#include "transfer.h"

enum AccountType { DEBIT, CHECKING };

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

#endif /*ACCOUNT_H*/

