#ifndef ACCOUNT_SERVICE_H
#define ACCOUNT_SERVICE_H

#include "../domain/account.h"

void create_account(Account *account);
void get_all_accounts();
void get_by_account_number(char *account_number, Account *account);

void update_balance(int account_id, double new_balance, Account *account);



#endif