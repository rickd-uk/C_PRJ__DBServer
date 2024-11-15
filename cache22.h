#ifndef CACHE22
#define CACHE22

#ifndef _GNU_SOURCE
#define _GNU_SOURCE
#endif
#include <arpa/inet.h>
#include <assert.h>
#include <errno.h>
#include <netinet/in.h>
#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define HOST "127.0.0.1"
#define PORT "12050"

/* #define log(x, args...) printf(x _VA_OPT_(, ) args) */
#define log(x, args...) printf(x, args)

typedef unsigned int int32;
typedef unsigned short int int16;
typedef unsigned char int8;

struct s_client {
  int s;
  char ip[16];
  int16 port;
};
typedef struct s_client Client;

void zero(int8 *, int16);
void child_loop(Client *);
void mainloop(int);
int initserver(int16 port);
int main(int, char **);

#endif
