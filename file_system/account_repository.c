#include <stdio.h>

#include "../repo/account_repository.h"

void save_account(Account *account){
     printf("### Creating account\n");

    // Abrir el archivo en modo de escritura binaria
    FILE *file = fopen("account.bin", "ab");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        //return 1;
    }

    fwrite(account, sizeof(Account), 1, file);

    // Cerrar el archivo
    fclose(file);
}

void fetch_all_accounts() {
    FILE *file = fopen("account.bin", "rb");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    Account account;
    while (fread(&account, sizeof(Account), 1, file) == 1) {
        printf("ID: %d\n", account.id);
        printf("Número de cuenta: %s\n", account.account_number);
        printf("Tipo de cuenta: %s\n", account.account_type == DEBIT ? "Débito" : "Corriente");
        printf("Saldo: %.2f\n", account.balance);
        printf("ID del cliente asociado: %d\n", account.client_id);
        printf("\n");
    }

    fclose(file);
}
