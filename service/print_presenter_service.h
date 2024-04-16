#ifndef PRINT_PRESENTER_SERVICE_H
#define PRINT_PRESENTER_SERVICE_H
#include "../domain/transaction.h"

void print_transaction_details(Transaction transaction);
void print_transfer_details(Transfer transfer, int account_id);
void print_headers(char *header);


#endif