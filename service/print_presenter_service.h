#ifndef PRINT_PRESENTER_SERVICE_H
#define PRINT_PRESENTER_SERVICE_H
#include "../domain/transaction.h"

// PRINT CLIENT
#define COLUMN_ID_WIDTH 10
#define COLUMN_NAME_WIDTH 30
#define COLUMN_DOCUMENT_WIDTH 20
#define COLUMN_ADDRESS_WIDTH 20
#define COLUMN_PHONE_WIDTH 20

void print_separator_line(int *column_widths, int num_columns);
void print_row(int *column_widths, char **data, int num_columns);

void print_transaction_details(Transaction transaction);
void print_transfer_details(Transfer transfer, int account_id);
void print_headers(char *header);


#endif