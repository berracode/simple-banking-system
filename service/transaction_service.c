#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include "transaction_service.h"
#include "transfer_service.h"
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
    // Buscar las transacciones por account_id
    Transaction *transactions;
    int len = fetch_by_account_id(account_id, &transactions);

    for (int i = 0; i < len; i++){
        printf("\n#########  TRANSACTION #%d  #########\n", (i+1));

        Transaction transaction = transactions[i];
        printf("\tTransaction ID: %d\n", transaction.id);
        printf("\tTransaction Type: %s\n", transaction.transaction_type == TRANSFER? "Transferencia": transaction.transaction_type == DEPOSIT? "Deposito": "Retiro");
        printf("\tAmount: %.2f\n", transaction.amount);
        printf("\tDate and Time: %s", ctime(&transaction.date_time));
        printf("\tAccount ID: %d\n", transaction.account_id);
        printf("\tTransfer ID: %d\n", transaction.transfer_id);

        if(transaction.transaction_type == TRANSFER){
            //BUSCAR LA transferencia para imprimir un buen detalle
            printf("\t\t|-------  TRANSACTION DETAIL  -------\n");
            Transfer transfer;
            get_transfer_by_id(transaction.transfer_id, &transfer);
            printf("\t\tTransfer ID: %d\n", transfer.id);
            printf("\t\t%s Amount: %.2f\n", transaction.account_id == transfer.origin_account ? "Outgoing": "Incoming", transfer.amount);
            printf("\t\t%s account: %d\n", transaction.account_id == transfer.destination_account ? "Origin": "Destination", transaction.account_id != transfer.origin_account? transfer.origin_account: transfer.destination_account);

        }
    }
    free(transactions);

}


