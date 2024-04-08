#include <stdio.h>

#include "../repo/client_repository.h"

void save_client(Client *client){
    printf("llamando adaptador secundario (que implementa puerto secundario o de salida)\n");

    // Abrir el archivo en modo de escritura binaria
    FILE *file = fopen("client.bin", "ab");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        //return 1;
    }

    // Escribir el número en el archivo
    fwrite(client, sizeof(Client), 1, file);

    // Cerrar el archivo
    fclose(file);
    

}

void fetch_all_clients() {
    FILE *file = fopen("client.bin", "rb");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    Client client;
    while (fread(&client, sizeof(Client), 1, file) == 1) {
        // Procesa cada cliente leído del archivo
        printf("ID: %d\n", client.id);
        printf("Nombre: %s\n", client.full_name);
        printf("Documento: %s\n", client.document);
        printf("Dirección: %s\n", client.address);
        printf("Teléfono: %s\n", client.phone_number);
        printf("\n");
    }

    fclose(file);
}

/**
 * This function serves as the foundation for searches using the AVL tree. 
 * The idea is to have an AVL tree in memory that contains the ID of each record 
 * (whether it be a client, account, transaction, or transfer), along with its "seek position," 
 * which is calculated at the beginning of this function.

How will it work? The ID of each record will be sequential, starting at 1, 
and each time a new record is added, its ID and its initial position in the file will be stored in a node of the AVL tree. 
For example, for the first record that is saved, since its "fixed size would be 264 bytes," 
the AVL tree node will store 1 as its ID and 0, which is the result of multiplying (1-1) * 264. 
For the sixth record, then, the AVL node will store 6 as its ID and 1320 for its position in the file. 
This way, when searching for the client with ID 2345, 
it is first searched in the AVL tree instead of traversing the file 2345 times.
*/
void fetch_by_random_index(int index) {
    long seek_position = (index-1) * sizeof(Client);
    printf("posicion a buscar: %ld\n", seek_position);

    FILE *file = fopen("client.bin", "rb");
    if (file == NULL) {
        perror("Error al abrir el archivo");
        return;
    }

    // move pointer's file to register position
    if (fseek(file, seek_position, SEEK_SET) != 0) {
        perror("Error al mover el puntero de archivo");
        fclose(file);
        return;
    }

    // Lee el registro deseado desde la posición actual en el archivo
    Client client;
    if (fread(&client, sizeof(Client), 1, file) != 1) {
        perror("Error al leer el registro");
        fclose(file);
        return;
    }

    // Imprime el registro leído
    printf("ID: %d\n", client.id);
    printf("Nombre: %s\n", client.full_name);
    printf("Documento: %s\n", client.document);
    printf("Dirección: %s\n", client.address);
    printf("Teléfono: %s\n", client.phone_number);

    fclose(file);

}



