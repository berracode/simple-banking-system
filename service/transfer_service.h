#ifndef TRANSFER_SERVICE_H
#define TRANSFER_SERVICE_H

#include "../domain/transfer.h"

void create_transfer(Transfer *transfer);

void get_transfer_by_id(const int transfer_id, Transfer *transfer);

#endif