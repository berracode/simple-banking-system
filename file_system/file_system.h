#ifndef FILE_SYSTEM_H
#define FILE_SYSTEM_H

enum BinFile{ CLIENT_FILE, ACCOUNT_FILE, TRANSACTION_FILE, TRANSFER_FILE};
enum ModeGetIndex{ INCREASE, READING};

int exists_directory(const char *path);
int path_valid(const char *path);
int get_index(enum BinFile bin_file, enum ModeGetIndex mode_get_index);

#endif