#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_system.h"
#include "../constants/constants.h"

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

    return result;
}

int get_index_from_file(const char *filename, enum ModeGetIndex mode_get_index) {
    // Abre el archivo si existe
    char *file_path = concatenate_filename(filename);
    int current_value = -1;
    FILE *file = fopen(file_path, "rb+");
    if (file == NULL && mode_get_index != READING) {
        file = fopen(file_path, "wb+");
        if (file == NULL) {
            perror("Error al abrir o crear el archivo");
            free(file_path);
            return -1;
        }
        fwrite(&current_value, sizeof(int), 1, file);
    } else if (file == NULL && mode_get_index == READING){
        //archivo no existe, y estoy tratando de leer el valor, entonces el valor es 0, por tanto no hay nada que leer
        current_value = -1;
    } else if (file != NULL && mode_get_index == READING){
        //archivo si existe, y estoy tratando de leer el valor, entonces es > 0
        fread(&current_value, sizeof(int), 1, file);
    } else {
        //archivo existe y estoy tratando de leer e incrementar su valor
        fread(&current_value, sizeof(int), 1, file);
        current_value++;
        fseek(file, 0, SEEK_SET);
        fwrite(&current_value, sizeof(int), 1, file);
    }
    if(file != NULL) {
        fclose(file);
    }
    free(file_path);

    return current_value;

}
int get_index(enum BinFile bin_file, enum ModeGetIndex mode_get_index) {
    const char *file_names[] = {CLIENT_INDEX, ACCOUNT_INDEX, TRANSACTION_INDEX, TRANSFER_INDEX};
    int index = -1;

    if (bin_file >= CLIENT_FILE && bin_file <= TRANSFER_FILE) {
        const char *file_name = file_names[bin_file];
        index = get_index_from_file(file_name, mode_get_index);
    }

    return index;
}