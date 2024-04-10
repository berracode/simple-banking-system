#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_system.h"

const char *BASE_INDEX = "index/";

char *concatenate_filename(const char *filename) {
    size_t base_len = strlen(BASE_INDEX);
    size_t filename_len = strlen(filename);
    char *result = malloc(base_len + filename_len + 1);
    if (result == NULL) {
        perror("Error al asignar memoria");
        exit(EXIT_FAILURE);
    }
    strcpy(result, BASE_INDEX);
    strcat(result, filename);
    printf("RUta completa: %s\n", result);

    return result;
}

int get_index_from_file(const char *filename) {
    // Abre el archivo si existe
    char *file_path = concatenate_filename(filename);
    FILE *file = fopen(file_path, "rb+");
    if (file == NULL) {
        file = fopen(file_path, "wb+"); //CREO UNO si no existe
        if (file == NULL) {
            perror("Error al abrir o crear el archivo");
            return -1; // Retorna un valor de error
        }
        int initial_value = 1;
        fwrite(&initial_value, sizeof(int), 1, file); //ESCRIBO EL VAlor inicial
        free(file_path);
        return initial_value;
    }

    int current_value;
    fread(&current_value, sizeof(int), 1, file);
    current_value++;
    fseek(file, 0, SEEK_SET);
    fwrite(&current_value, sizeof(int), 1, file);

    fclose(file);
    free(file_path);

    return current_value;
}

int get_index(enum BinFile bin_file) {

    const char *file_name;

    int index;

    switch (bin_file) {
        case CLIENT_FILE:
            file_name = "client_index";
            index = get_index_from_file(file_name);
            break;
        case ACCOUNT_FILE:
            file_name = "account_index";
            index = get_index_from_file(file_name);
            break;
        case TRANSACTION_FILE:
            file_name = "transaction_index";
            index = get_index_from_file(file_name);
            break;
        case TRANSFER_FILE:
            file_name = "transfer_index";
            index = get_index_from_file(file_name);
            break;
        default:
            return -1;
            break;
    }

    return index;

}