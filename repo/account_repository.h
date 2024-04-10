#ifndef ACCOUNT_REPOSITORY_H
#define ACCOUNT_REPOSITORY_H

#include "../domain/account.h"

void save_account(Account *account);
void fetch_all_accounts();


#endif /* ACCOUNT_REPOSITORY_H */