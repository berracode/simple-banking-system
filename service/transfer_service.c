#include <stdio.h>
#include <stddef.h>
#include "transfer_service.h"
#include "../repo/transfer_repository.h"

void create_transfer(Transfer *transfer){
    printf("-----------------------------------\n");
    printf("Creating transfer...\n");
    printf("ID: %d\n", transfer->id);
    printf("Amount: %f\n", transfer->amount);
    printf("Origin: %d\n", transfer->origin_account);
    printf("Destination: %d\n", transfer->destination_account);

    register_transfer(transfer);
    printf("-----------------------------------\n\n");


}


