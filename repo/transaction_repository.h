#ifndef TRANSACTION_REPOSITORY_H
#define TRANSACTION_REPOSITORY_H

#include "../domain/transaction.h"

// Función para registrar una transacción
void register_transaction(Transaction *transaction);
void fetch_by_account_id(int account_id);

#endif /* TRANSACTION_REPOSITORY_H */