#include <stdio.h>
#include <string.h>
#include <time.h>


#include "file_system.h"
#include "../constants/constants.h"
#include "../repo/transaction_repository.h"

void register_transaction(Transaction *transaction){
     printf("### Creating transaction\n");

    // Abrir el archivo en modo de escritura binaria
    FILE *file = fopen(TRANSACTION_DB, "ab");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        //return 1;
    }

    transaction->id = get_index(TRANSACTION_FILE);
    printf("real id transaction: %d", transaction->id);
    time_t current_time;
    time(&current_time);
    transaction->date_time = current_time;
    printf("Fecha y hora actual de la transaccion: %s", ctime(&transaction->date_time));

    fwrite(transaction, sizeof(Transaction), 1, file);
    fclose(file);
}


void fetch_by_account_id(int account_id) {

    FILE *file = fopen(TRANSACTION_DB, "rb");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    int found = 0;
    Transaction transaction;
    while (fread(&transaction, sizeof(Transaction), 1, file) == 1) {
        if (transaction.account_id == account_id) {
            printf("Transaction ID: %d\n", transaction.id);
            printf("Transaction Type: %s\n", transaction.transaction_type == TRANSFER? "Transferencia": transaction.transaction_type == DEPOSIT? "Deposito": "Retiro");
            printf("Amount: %.2f\n", transaction.amount);
            printf("Date and Time: %s", ctime(&transaction.date_time));
            printf("Account ID: %d\n", transaction.account_id);
            printf("Transfer ID: %d\n", transaction.transfer_id);

            found = 1;
        }
    }

    if (!found) {
        printf("No se encontraron transacciones para el account ID: %d\n", account_id);
    }

    fclose(file);
}