#include <stdio.h>
#include <stddef.h>
#include "../repo/account_repository.h"


void create_account(Account *account){
    printf("Creando cuenta...\n");
    printf("ID: %d\n", account->id);
    printf("Número de cuenta: %s\n", account->account_number);
    printf("Tipo de cuenta: %s\n", account->account_type == DEBIT ? "Ahorros" : "Corriente");
    printf("Balance: %.2f\n", account->balance);
    printf("ID del cliente asociado: %d\n", account->client_id);

    save_account(account);
}

void get_all_accounts(){
    //to do

    fetch_all_accounts();
}
