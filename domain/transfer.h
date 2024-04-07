#ifndef TRANSFER_H
#define TRANSFER_H

#include <time.h>

typedef struct {
    int id;
    double amount;
    time_t date_time;
    int origin_account;
    int destination_account;
} Transfer;


#endif