#include <stdio.h>
#include <stdlib.h> // Incluimos stdlib.h para usar malloc

#include <string.h>

#include "../repo/client_repository.h"
#include "print_util.h"

int column_widths[] = {COLUMN_ID_WIDTH, COLUMN_NAME_WIDTH, COLUMN_DOCUMENT_WIDTH, COLUMN_ADDRESS_WIDTH, COLUMN_PHONE_WIDTH};

char *headers[] = {"ID", "Nombre", "Documento", "Direccion", "Telefono"};

void save_client(Client *client)
{
    printf("llamando adaptador secundario (que implementa puerto secundario o de salida)\n");

    // Abrir el archivo en modo de escritura binaria
    FILE *file = fopen("client.bin", "ab");
    if (file == NULL)
    {
        perror("Error al abrir el archivo");
        // return 1;
    }

    // Escribir el número en el archivo
    fwrite(client, sizeof(Client), 1, file);

    // Cerrar el archivo
    fclose(file);
}

void fetch_all_clients()
{
    FILE *file = fopen("client.bin", "rb");
    if (file == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    print_separator_line(column_widths, sizeof(column_widths) / sizeof(column_widths[0]));
    print_row(column_widths, headers, sizeof(headers) / sizeof(headers[0]));
    print_separator_line(column_widths, sizeof(column_widths) / sizeof(column_widths[0]));

    Client client;
    while (fread(&client, sizeof(Client), 1, file) == 1)
    {
       char **data = malloc(5 * sizeof(char *));
            if (data == NULL){
                perror("Error: No se pudo asignar memoria para data");
                return;
            }
            for (int i = 0; i < 5; i++){
                data[i] = malloc((column_widths[i] + 1) * sizeof(char));
                if (data[i] == NULL){
                    perror("Error: No se pudo asignar memoria para data[i]");
                    return;
                }
            }
            snprintf(data[0], column_widths[0] + 1, "%d", client.id);
            strcpy(data[1], client.full_name);
            strcpy(data[2], client.document);
            strcpy(data[3], client.address);
            strcpy(data[4], client.phone_number);
            print_row(column_widths, data, 5);

            for (int i = 0; i < 5; i++){
                free(data[i]);
            }
            free(data);
            print_separator_line(column_widths, sizeof(column_widths) / sizeof(column_widths[0]));
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
void fetch_by_random_index(int index)
{
    long seek_position = (index - 1) * sizeof(Client);
    printf("posicion a buscar: %ld\n", seek_position);

    FILE *file = fopen("client.bin", "rb");
    if (file == NULL)
    {
        perror("Error al abrir el archivo");
        return;
    }

    // move pointer's file to register position
    if (fseek(file, seek_position, SEEK_SET) != 0)
    {
        perror("Error al mover el puntero de archivo");
        fclose(file);
        return;
    }

    // Lee el registro deseado desde la posición actual en el archivo
    Client client;
    if (fread(&client, sizeof(Client), 1, file) != 1)
    {
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

void fetch_by_document(const char *document, Client *client)
{

    printf("client to find: %s\n", document);

    FILE *file = fopen("client.bin", "rb");
    if (file == NULL)
    {
        perror("Error al abrir el archivo\n");
        client->id = -1;
        return;
    }

    int found = 0;

    print_separator_line(column_widths, sizeof(column_widths) / sizeof(column_widths[0]));
    print_row(column_widths, headers, sizeof(headers) / sizeof(headers[0]));
    print_separator_line(column_widths, sizeof(column_widths) / sizeof(column_widths[0]));

    while (fread(client, sizeof(Client), 1, file) == 1)
    {
        if (strcmp(document, client->document) == 0){
            found = 1;
            char **data = malloc(5 * sizeof(char *));
            if (data == NULL){
                perror("Error: No se pudo asignar memoria para data");
                return;
            }
            for (int i = 0; i < 5; i++){
                data[i] = malloc((column_widths[i] + 1) * sizeof(char));
                if (data[i] == NULL){
                    perror("Error: No se pudo asignar memoria para data[i]");
                    return;
                }
            }
            snprintf(data[0], column_widths[0] + 1, "%d", client->id);
            strcpy(data[1], client->full_name);
            strcpy(data[2], client->document);
            strcpy(data[3], client->address);
            strcpy(data[4], client->phone_number);
            print_row(column_widths, data, 5);

            for (int i = 0; i < 5; i++){
                free(data[i]);
            }
            free(data);
            print_separator_line(column_widths, sizeof(column_widths) / sizeof(column_widths[0]));
            break;
        }
    }
    if (!found)
    {
        printf("Client with document %s was not found\n", document);
        client->id = -1;
    }
    fclose(file);
}
