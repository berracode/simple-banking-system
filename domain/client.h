#ifndef CLIENT_H
#define CLIENT_H

#include "account.h"

typedef struct {
    int id;
    char full_name[100];
    char document[30];
    char address[100];
    char phone_number[20];

    //puntero
    struct Account *accounts; //account's list
} Client;

#endif 