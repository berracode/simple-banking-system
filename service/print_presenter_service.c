#include <stdio.h>
#include "print_presenter_service.h"


void print_separator_line(int *column_widths, int num_columns) {
    int total_width = (num_columns-1)+num_columns*2;
    for (int i = 0; i < num_columns; ++i) {
        total_width += column_widths[i];
    }
    printf("+");
    for (int i = 0; i < total_width; ++i) {
        printf("-");
    }
    printf("+\n");
}

void print_row(int *column_widths, char **data, int num_columns) {
    printf("|");
    for (int i = 0; i < num_columns; i++) {
        //printf("col %d tam: %d", i, column_widths[i]);
        printf(" %-*s |", column_widths[i], data[i]);
    }
    printf("\n");
}

void print_transaction_details(Transaction transaction) {
   /* printf("Transaction ID: %d\n", transaction.id);
    printf("Transaction Type: %s\n", 
           transaction.transaction_type == TRANSFER ? "Transferencia" : 
           transaction.transaction_type == DEPOSIT ? "Depósito" : "Retiro");
    printf("Amount: %.2f\n", transaction.amount);
    printf("Date and Time: %s", ctime(&transaction.date_time));
    printf("Account ID: %d\n", transaction.account_id);
    printf("Transfer ID: %d\n", transaction.transfer_id);*/

    printf("%-12d %-16s %-8.2f %-20s %-10d %-12d\n",
        transaction.id,
        transaction.transaction_type == TRANSFER ? "Transferencia" :
        transaction.transaction_type == DEPOSIT ? "Depósito" : "Retiro",
        transaction.amount,
        ctime(&transaction.date_time),
        transaction.account_id,
        transaction.transfer_id);


}

void print_transfer_details(Transfer transfer, int account_id) {
    printf("|TRANSFER DETAIL\n|\n");
    printf("|Transfer ID: %d\n", transfer.id);
    printf("|%s Amount: %.2f\n", account_id == transfer.origin_account ? "Outgoing" : "Incoming", transfer.amount);
    printf("|%s account: %d\n", account_id == transfer.destination_account ? "Origin" : "Destination", 
           account_id != transfer.origin_account ? transfer.origin_account : transfer.destination_account);
}

void print_headers(char *header) {
    printf("\t\t#####  %s  #####\n\n", header);
}
