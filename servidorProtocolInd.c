#include <stdio.h>//snprintf
#include <stdlib.h>//exit
#include <string.h>//bzero, strlen
#include <unistd.h> //fork, close, write
#include <time.h> // Tirar se não for mais necessário.
#include <errno.h>
#include "wraper.h"

int main (int argc, char **argv) {
  socklen_t len, addrlen;
  int    listenfd, connfd;
  struct sockaddr_storage cliaddr; //cliaddr;
  char   buff[MAXDATASIZE];
  time_t ticks;
  pid_t pid;

  switch (argc) {
    case 1:
      listenfd = tcp_listen(NULL, "13", &addrlen);
      break;
    case 2:
      listenfd = tcp_listen(NULL, argv[1], &addrlen);
      break;
    case 3:
      listenfd = tcp_listen(argv[1], argv[2], &addrlen);
      break;
    default:
      err_quit("usage: daytimetcpsrv2 [ <host>] <service or port>");
  }

  for ( ; ; ) {
    len = sizeof(cliaddr) ;
    connfd = Accept(listenfd, (struct sockaddr *) &cliaddr, &len);

    if ((pid = fork()) == 0) {
      Close(listenfd);
      ticks = time(NULL);
      snprintf(buff, sizeof(buff), "%.20s\r\n", ctime(&ticks));
      Write(connfd, buff, strlen(buff));
      shutdown(connfd, SHUT_RDWR);
      exit(0);
    }

  }
  return(0);
}
