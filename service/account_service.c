#include <stdio.h>
#include <stddef.h>
#include "../repo/account_repository.h"

void create_account(Account *account){
    printf("Creating account...\n");
    printf("ID: %d\n", account->id);
    printf("Número de cuenta: %s\n", account->account_number);
    printf("Tipo de cuenta: %s\n", account->account_type == SAVINGS ? "Ahorros" : "Corriente");
    printf("Balance: %.2f\n", account->balance);
    printf("ID del cliente asociado: %d\n", account->client_id);

    save_account(account);
}

void get_all_accounts(){
    //to do

    fetch_all_accounts();
}


void get_by_account_number(char *account_number, Account *account) {

    *account = fetch_by_account_number(account_number);
    printf("account id: %d\n", account->id);
    printf("account balance: %f\n", account->balance);
    if(account->id == -1 ){
        printf("Account does not exist!");
        return;
    }

}

void update_balance(int account_id, double new_balance, Account *account) {
    printf("------------------------------------\n\n");
    printf("Updating balance in account number: %s\n", account->account_number);
    printf("Updating balance in account id: %d\n", account_id);

    printf("Balance actual: %f\n", account->balance);
    account->balance = new_balance;
    edit_account(account);
    printf("new Balance actual: %f\n", account->balance);
    printf("Validating with file...\n");
    Account account_validated;
    get_by_account_number(account->account_number, &account_validated);
    printf("new Balance actual validado: %f\n", account_validated.balance);

    printf("------------------------------------\n\n");

}


