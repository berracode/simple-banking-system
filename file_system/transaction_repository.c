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

