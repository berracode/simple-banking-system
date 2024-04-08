#ifndef TRANSACTION_H
#define TRANSACTION_H

#include <time.h>
#include "transfer.h"


enum TransactionType { DEPOSIT, WITHDRAWAL, TRANSFER };

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

#endif /*TRANSACTION_H*/