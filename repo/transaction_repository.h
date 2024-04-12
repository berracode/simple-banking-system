#ifndef TRANSACTION_REPOSITORY_H
#define TRANSACTION_REPOSITORY_H

#include "../domain/transaction.h"

// Función para registrar una transacción
void register_transaction(Transaction *transaction);
int fetch_by_account_id(int account_id, Transaction **transactions);

#endif /* TRANSACTION_REPOSITORY_H */