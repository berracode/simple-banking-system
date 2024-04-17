#include <stdio.h>
#include <string.h>

#include "file_system.h"
#include "../constants/constants.h"
#include "../repo/account_repository.h"

void save_account(Account *account){
    printf("\t\tCreating account on file\n");

    FILE *file = fopen(ACCOUNT_DB, "ab");
    if (file == NULL) {
        perror("Error opening file!");
        return;
    }

    account->id = get_index(ACCOUNT_FILE, INCREASE);
    if(account->id == -1){
        printf("Could not save account\n");
        return;
    }

    fwrite(account, sizeof(Account), 1, file);

    fclose(file);
}

void fetch_all_accounts() {
    FILE *file = fopen(ACCOUNT_DB, "rb");
    if (file == NULL) {
        perror("Error opening file");
        return;
    }

    Account account;
    while (fread(&account, sizeof(Account), 1, file) == 1) {
        //linked list for this. Don't print info in repos
        printf("ID: %d\n", account.id);
        printf("Número de cuenta: %s\n", account.account_number);
        printf("Tipo de cuenta: %s\n", account.account_type == SAVINGS ? "Ahorros" : "Corriente");
        printf("Saldo: %.2f\n", account.balance);
        printf("ID del cliente asociado: %d\n", account.client_id);
        printf("\n");
    }

    fclose(file);
}

Account fetch_by_account_number(const char *account_number){
    printf("\t\t...Account to find on file: %s\n", account_number);
    Account account;

    FILE *file = fopen(ACCOUNT_DB, "rb");
    if (file == NULL) {
        perror("Error opening file!\n");
        account.id = -1;
        return account;
    }

    while (fread(&account, sizeof(Account), 1, file)==1){
        if(strcmp(account_number, account.account_number)==0){
            return account;
        }
    }

    account.id = -1;
    return account;

}

void edit_account(Account *account) {
    printf("\t\tEditing account...\n");
    //printf("ACCOUNT SIZE: %zu\n", sizeof(Account));
    long seek_position = (account->id - 1) * sizeof(Account);
    //printf("posicion a buscar: %ld\n", seek_position);

    FILE *file = fopen(ACCOUNT_DB, "r+b");
    if (file == NULL) {
        perror("Error opening file!\n");
        return;
    }

      // move pointer's file to register position
    if (fseek(file, seek_position, SEEK_SET) != 0){
        perror("Error moving pointer");
        fclose(file);
        return;
    }

    fwrite(account, sizeof(Account), 1, file);

    fclose(file);

}
