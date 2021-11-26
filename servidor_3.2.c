#include <stdio.h>//snprintf
#include <stdlib.h>//exit
#include <string.h>//bzero, strlen
#include <unistd.h> //fork, close, write
#include <time.h> // Tirar se não for mais necessário.
#include <errno.h>
#include "wraper.h"

#define LISTENQ 10
#define MAXDATASIZE 100

int main (int argc, char **argv) {
   int    listenfd, connfd;
   struct sockaddr_in servaddr; //cliaddr;
   char   buf[MAXDATASIZE];
   time_t ticks;
   pid_t pid;

   listenfd = Socket (AF_INET, SOCK_STREAM, 0);

   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family      = AF_INET;
   servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
   servaddr.sin_port        = htons(13);
  
   Bind(listenfd, (struct sockaddr *)&servaddr, sizeof (servaddr));
  
   Listen(listenfd, LISTENQ);

   for ( ; ; ) {
      connfd = Accept(listenfd, (struct sockaddr *) NULL, NULL);

      if ( (pid = fork()) == 0) {
        close(listenfd);
        ticks = time(NULL);
        snprintf(buf, sizeof(buf), "%.20s\r\n", ctime(&ticks));
        write(connfd, buf, strlen(buf));
        //getpeername(connfd, (struct sockaddr *)&cliaddr, (socklen_t * restrict) sizeof(cliaddr));
        //printf("%d\n", cliaddr.sin_addr);
        //sleep(30);//Teste de concorrência.
        shutdown(connfd, SHUT_RDWR);
        exit(0);
      }
   }
   return(0);
}
