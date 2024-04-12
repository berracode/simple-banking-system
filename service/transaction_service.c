#include <stdio.h>
#include <stddef.h>
#include "transaction_service.h"
#include "../repo/transaction_repository.h"

void create_transaction(Transaction *transaction){
    printf("-----------------------------------\n");

    printf("Creating transaction...\n");
    printf("ID: %d\n", transaction->id);
    printf("Amount: %f\n", transaction->amount);
    printf("Origin: %d\n", transaction->account_id);
    printf("Tipo de transaccion: %s\n", transaction->transaction_type == TRANSFER ? "Transferencia" : "OTROS");
    printf("ID Transferencia: %d\n", transaction->transfer_id);

    register_transaction(transaction);
    printf("-----------------------------------\n\n");

}

void get_by_account_id(int account_id) {
    fetch_by_account_id(account_id);
}


