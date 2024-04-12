#include <stdio.h>
#include "print_presenter_service.h"

void print_transaction_details(Transaction transaction) {
    printf("Transaction ID: %d\n", transaction.id);
    printf("Transaction Type: %s\n", 
           transaction.transaction_type == TRANSFER ? "Transferencia" : 
           transaction.transaction_type == DEPOSIT ? "Depósito" : "Retiro");
    printf("Amount: %.2f\n", transaction.amount);
    printf("Date and Time: %s", ctime(&transaction.date_time));
    printf("Account ID: %d\n", transaction.account_id);
    printf("Transfer ID: %d\n", transaction.transfer_id);
}

void print_transfer_details(Transfer transfer, int account_id) {
    printf("\t\t|-------  TRANSACTION DETAIL  -------\n");
    printf("\t\tTransfer ID: %d\n", transfer.id);
    printf("\t\t%s Amount: %.2f\n", account_id == transfer.origin_account ? "Outgoing" : "Incoming", transfer.amount);
    printf("\t\t%s account: %d\n", account_id == transfer.destination_account ? "Origin" : "Destination", 
           account_id != transfer.origin_account ? transfer.origin_account : transfer.destination_account);
}