#include "cache22.h"

bool scontinue;

void mainloop(int s) {
  struct sockaddr_in cli;
  int s2;
  int32 len;
  char *ip;
  int16 port;

  s2 = accept(s, (struct sockaddr *)&cli, &len);
  if (s2 < 0) return;

  port = (int16)htons((int)cli.sin_port);

  ip = inet_ntoa(cli.sin_addr);
  printf("Connection from %s:%d\n", ip, port);
  ;
}

int initserver(int16 port) {
  struct sockaddr_in sock;
  int s;

  sock.sin_family = AF_INET;
  sock.sin_port = htons(port);
  sock.sin_addr.s_addr = inet_addr(HOST);

  s = socket(AF_INET, SOCK_STREAM, 0);
  /* printf("S = %d\n", s); */
  assert(s > 0);

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
