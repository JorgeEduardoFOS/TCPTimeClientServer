#include <stdio.h>//perror
#include <errno.h>
#include <string.h>//strcpy, strcat, bzero
#include <stdlib.h>//exit
#include <unistd.h>//read
#include "wraper.h"

#define MAXLINE 4096

int main(int argc, char **argv) {
   int    sockfd, n;
   char   recvline[MAXLINE + 1];
   char   error[MAXLINE + 1];
   struct sockaddr_in servaddr;

   if (argc != 2) {
      strcpy(error,"uso: ");
      strcat(error,argv[0]);
      strcat(error," <IPaddress>");
      perror(error);
      exit(1);
   }
                                  
   sockfd = socket (AF_INET, SOCK_STREAM, 0);

   bzero(&servaddr, sizeof(servaddr));
   servaddr.sin_family = AF_INET;
   servaddr.sin_port   = htons(13);
   
   Inet_pton(AF_INET, argv[1], &servaddr.sin_addr);
  
   Connect(sockfd, (struct sockaddr *) &servaddr, sizeof(servaddr));

   while ( (n = read(sockfd, recvline, MAXLINE)) > 0) {
      recvline[n] = 0;
      Fputs (recvline, stdout);
   }

   if (n < 0) {
      perror("read error");
      exit(1);
   }

   exit(0);
}
