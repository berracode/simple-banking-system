#ifndef TRANSACTION_SERVICE_H
#define TRANSACTION_SERVICE_H

#include "../domain/transaction.h"

void create_transaction(Transaction *transaction);
void get_by_account_id(int account_id);

#endif