#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli/cli.h"

enum AccountType { DEBIT, CHECKING };


int main() {
    system("clear");
    enum AccountType t;
    printf("Size of Client struct: %zu bytes\n", sizeof(int));
    printf("Size of AT ENUM: %zu bytes\n", sizeof(t));
    commands_init(); 
    
    return 0;
}