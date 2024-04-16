#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


#include "file_system.h"
#include "../constants/constants.h"
#include "../repo/transaction_repository.h"

void register_transaction(Transaction *transaction){
    //printf("### Creating transaction\n");

    // Abrir el archivo en modo de escritura binaria
    FILE *file = fopen(TRANSACTION_DB, "ab");
    if (file == NULL) {
        perror("Error opening file!\n");
        return;
    }

    transaction->id = get_index(TRANSACTION_FILE, INCREASE);
    if(transaction->id == -1){
        printf("Could not save transaction\n");
        return;
    }
    //printf("real id transaction: %d", transaction->id);
    time_t current_time;
    time(&current_time);
    transaction->date_time = current_time;
    //printf("Fecha y hora actual de la transaccion: %s", ctime(&transaction->date_time));

    fwrite(transaction, sizeof(Transaction), 1, file);
    fclose(file);
}


int fetch_by_account_id(int account_id, Transaction **transactions) {

    FILE *file = fopen(TRANSACTION_DB, "rb");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return 0;
    }

    int transactions_size = get_index(TRANSACTION_FILE, READING);
    printf("Size of transactions: %d\n", transactions_size);
    if(transactions_size == -1){
        printf("No hay transacciones");
        return 0;
    }

    // Crear un arreglo dinámico para almacenar las transacciones
    printf("REAL STRUCT TRANSACTIONS SIZE: %zu\n", sizeof(Transaction));
    *transactions = (Transaction *)malloc(transactions_size * sizeof(Transaction));
    if (*transactions == NULL) {
        perror("Error al asignar memoria para las transacciones");
        fclose(file);
        return 0;
    }

    int found = 0, num_transactions=0;
    Transaction transaction;
    while (fread(&transaction, sizeof(Transaction), 1, file) == 1) {
        if (transaction.account_id == account_id) {
            (*transactions)[num_transactions] = transaction;
            found = 1;
            num_transactions++;
        }
    }

    if (!found) {
        printf("No se encontraron transacciones para el account ID: %d\n", account_id);
    }

    fclose(file);
    return num_transactions;

}