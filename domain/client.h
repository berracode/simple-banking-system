#ifndef CLIENT_H
#define CLIENT_H
#include <stdio.h>
#include "account.h"

typedef struct {
    int id;
    char full_name[100];
    char document[30];
    char address[100];
    char phone_number[20];
    char password[10];

    //puntero
    struct Account *accounts; //account's list
} Client;

void print_client(Client *client);

#endif /* CLIENT_H */