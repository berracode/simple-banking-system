#ifndef ACCOUNT_REPOSITORY_H
#define ACCOUNT_REPOSITORY_H

#include "../domain/account.h"

void save_account(Account *account);
void fetch_all_accounts();
Account fetch_by_account_number(const char *account_number);

void edit_account(Account *account);

#endif /* ACCOUNT_REPOSITORY_H */