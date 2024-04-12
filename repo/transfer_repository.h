#ifndef TRANSFER_REPOSITORY_H
#define TRANSFER_REPOSITORY_H

#include "../domain/transfer.h"

// Función para transferir dinero
void register_transfer(Transfer *transfer);
void fetch_by_transfer_id(const int transfer_id, Transfer *transfer_to_find);

#endif /* TRANSFER_REPOSITORY_H */