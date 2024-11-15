#include "cache22.h"

bool scontinue;
bool child_continue;

void zero(int8 *buf, int16 size) {
  int8 *p;
  int16 n;

  for (n = 0, p = buf; n < size; n++, p++) *p = 0;

  return;
}

void child_loop(Client *cli) {
  sleep(1);

  return;
}

void mainloop(int s) {
  struct sockaddr_in cli;
  int s2;
  socklen_t len = sizeof(cli);
  char *ip;
  int16 port;
  Client *client;
  pid_t pid;

  s2 = accept(s, (struct sockaddr *)&cli, &len);
  if (s2 < 0) return;

  /* close(s2); */

  port = ntohs(cli.sin_port);
  ip = inet_ntoa(cli.sin_addr);

  printf("Connection from %s:%d\n", ip, port);

  client = (Client *)malloc(sizeof(struct s_client));
  assert(client);

  zero((int8 *)client, sizeof(struct s_client));

  client->s = s;
  client->port = port;
  strncpy(client->ip, ip, 15);

  pid = fork();
  if (pid) {
    free(client);
    return;
  } else {
    dprintf(s2, "100 Connected to Cache22 server \n");
    child_continue = true;
    while (child_continue) child_loop(client);
    close(s2);
    free(client);
    return;
  }
}

int initserver(int16 port) {
  struct sockaddr_in sock;
  int s;

  sock.sin_family = AF_INET;
  sock.sin_port = htons(port);
  sock.sin_addr.s_addr = inet_addr(HOST);

  s = socket(AF_INET, SOCK_STREAM, 0);
  /* printf("S = %d\n", s); */
  assert(s >= 0);

  errno = 0;
  if (bind(s, (struct sockaddr *)&sock, sizeof(sock))) assert_perror(errno);

  errno = 0;
  if (listen(s, 20))  // accept 20 connections
    assert_perror(errno);

  /* log("Server listening on %s:%d", HOST, port); */
  printf("Server listening on %s:%d\n", HOST, port);
  return s;
}

int main(int argc, char *argv[]) {
  char *sport;
  int16 port;
  int s;

  if (argc < 2)
    sport = PORT;
  else
    sport = argv[1];

  port = (int16)atoi(sport);

  s = initserver(port);

  scontinue = true;
  while (scontinue) {
    mainloop(s);
  }
  printf("Closing server.\n");
  close(s);

  return 0;
}
