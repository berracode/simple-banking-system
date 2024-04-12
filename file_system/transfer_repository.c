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

    transfer->id = get_index(TRANSFER_FILE, INCREASE);
    if(transfer->id == -1){
        printf("Could not save transfer\n");
        return;
    }
    printf("Real transfer id: %d\n", transfer->id);
    time_t current_time;
    time(&current_time);
    transfer->date_time = current_time;
    printf("Fecha y hora actual de la transferencia: %s\n", ctime(&transfer->date_time));



    fwrite(transfer, sizeof(Transfer), 1, file);

    // Cerrar el archivo
    fclose(file);
}

void fetch_by_transfer_id(const int transfer_id, Transfer *transfer_to_find){


    //printf("transfer to find: %d\n", transfer_id);

    FILE *file = fopen(TRANSFER_DB, "rb");
    if (file == NULL)
    {
        perror("Error al abrir el archivo\n");
        transfer_to_find->id = -1;
        return;
    }

    int found = 0;

    Transfer transfer;
    while (fread(&transfer, sizeof(Transfer), 1, file) == 1)
    {
        if (transfer_id == transfer.id){
            found = 1;
            memcpy(transfer_to_find, &transfer, sizeof(Transfer));
            break;
        }
    }
    if (!found)
    {
        printf("Transfer with ID %d was not found\n", transfer_id);
        transfer_to_find->id = -1;
    }
    fclose(file);
}


