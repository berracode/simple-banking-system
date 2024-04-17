#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

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

    printf("\n#########  TRANSACTIONS  #########\n");


    int column_widths[] = {10, 16, 15, 25, 15, 15};
    char *headers[] = {"ID", "TRANSACTION TYPE", "AMOUNT", "DATE", "ACCOUNT ID", "TRANSFER ID"};


    print_separator_line(column_widths, sizeof(column_widths) / sizeof(column_widths[0]));
    print_row(column_widths, headers, sizeof(headers) / sizeof(headers[0]));
    print_separator_line(column_widths, sizeof(column_widths) / sizeof(column_widths[0]));

    for (int i = 0; i < len; i++){
        //printf("--------------------------------------------------\n\n");
        //printf("TRANSACTION #%dn", (i+1));
        Transaction transaction = transactions[i];
        char **data = malloc(6 * sizeof(char *));
        if (data == NULL){
            perror("Error: No se pudo asignar memoria para data");
            return;
        }
        for (int i = 0; i < 6; i++){
            data[i] = malloc((column_widths[i] + 1) * sizeof(char));
            if (data[i] == NULL){
                perror("Error: No se pudo asignar memoria para data[i]");
                return;
            }
        }

        snprintf(data[0], column_widths[0] + 1, "%d", transaction.id);
        strcpy(data[1], transaction.transaction_type == TRANSFER ? "TRANSFER" :
        transaction.transaction_type == DEPOSIT ? "DEPOSIT" : "WITHDRAWAL");
        snprintf(data[2], column_widths[2] + 1, "%lf", transaction.amount);
        strcpy(data[3], ctime(&transaction.date_time));
        size_t len = strlen(data[3]);
        if (len > 0 && data[3][len - 1] == '\n') {
            data[3][len - 1] = '\0';
        }
        snprintf(data[4], column_widths[4] + 1, "%d", transaction.account_id);
        snprintf(data[5], column_widths[5] + 1, "%d", transaction.transfer_id);

        print_row(column_widths, data, 6);

        //print_transaction_details(transaction);

       if(transaction.transaction_type == TRANSFER){
            //BUSCAR LA transferencia para imprimir un buen detalle
            Transfer transfer;
            get_transfer_by_id(transaction.transfer_id, &transfer);
            print_transfer_details(transfer, transaction.account_id);

        }

        free(data);
        print_separator_line(column_widths, sizeof(column_widths) / sizeof(column_widths[0]));
    }
    free(transactions);

}


