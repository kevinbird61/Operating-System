#include <stdio.h>
#include <stdlib.h>
#include "myfile.h"
#define READBUF 512

/* Start to fetch user command */
void fetch_command();
char *command_read();
int command_execute();
