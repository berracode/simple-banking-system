#include <stdio.h>
#include <string.h>
#include <time.h>


#include "file_system.h"
#include "../constants/constants.h"
#include "../repo/transfer_repository.h"

void register_transfer(Transfer *transfer){
    printf("### Creating transfer on file\n");

    // Abrir el archivo en modo de escritura binaria
    FILE *file = fopen(TRANSFER_DB, "ab");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        //return 1;
    }

    transfer->id = get_index(TRANSFER_FILE);
    printf("Real transfer id: %d\n", transfer->id);
    time_t current_time;
    time(&current_time);
    transfer->date_time = current_time;
    printf("Fecha y hora actual de la transferencia: %s\n", ctime(&transfer->date_time));



    fwrite(transfer, sizeof(Transfer), 1, file);

    // Cerrar el archivo
    fclose(file);
}

