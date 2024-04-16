#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "transaction_service.h"
#include "transfer_service.h"
#include "../repo/transaction_repository.h"
#include "../service/print_presenter_service.h"

void create_transaction(Transaction *transaction){
    //printf("-----------------------------------\n");

    printf("Creating transaction...\n");
    //printf("ID: %d\n", transaction->id);
    //printf("Amount: %f\n", transaction->amount);
    //printf("Origin: %d\n", transaction->account_id);
    //printf("Tipo de transaccion: %s\n", transaction->transaction_type == TRANSFER ? "Transferencia" : "OTROS");
    //printf("ID Transferencia: %d\n", transaction->transfer_id);

    register_transaction(transaction);
    //printf("-----------------------------------\n\n");

}

void get_by_account_id(int account_id) {
    // Buscar las transacciones por account_id
    Transaction *transactions;
    int len = fetch_by_account_id(account_id, &transactions);

    for (int i = 0; i < len; i++){
        printf("\n#########  TRANSACTION #%d  #########\n", (i+1));

        Transaction transaction = transactions[i];
        print_transaction_details(transaction);

        if(transaction.transaction_type == TRANSFER){
            //BUSCAR LA transferencia para imprimir un buen detalle
            Transfer transfer;
            get_transfer_by_id(transaction.transfer_id, &transfer);
            print_transfer_details(transfer, transaction.account_id);
        }
    }
    free(transactions);

}


