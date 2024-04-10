#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cli/cli.h"

int main() {
    system("clear");
    printf("Size of Client struct: %zu bytes\n", sizeof(int));
    commands_init(); 
    
    return 0;
}