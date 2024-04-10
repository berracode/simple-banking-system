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