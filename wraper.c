#include <stdio.h>//perror
#include <stdlib.h>//exit
#include <errno.h>
#include <arpa/inet.h>//inet_peton
#include "wraper.h"

int listenfd, connfd;

int Socket(int domain, int type, int protocol){
  if ((listenfd = socket(domain, type, protocol)) == -1) {
      perror("socket");
      exit(1);
   }
  else
    return listenfd;
}

void Inet_pton(int af, const char *restrict src, void *restrict dst){
  if (inet_pton(af, src, dst) <= 0) {
      perror("inet_pton error");
      exit(1);
   }
}

void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
  if (bind(sockfd, addr, addrlen) == -1) {
      perror("bind");
      exit(1);
  }
}

void Fputs(const char *restrict s, FILE *restrict fluxo){
  if (fputs(s, fluxo) == EOF) {
         perror("fputs error");
         exit(1);
      }
}

void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen){
  if (connect(sockfd, addr, addrlen) < 0) {
      perror("connect error");
      exit(1);
   }
}

void Listen(int sockfd, int backlog){
  if (listen(sockfd, backlog) == -1) {
      perror("listen");
      exit(1);
   }
}
                                                                       
int Accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen){
  if ((connfd = accept(sockfd, (struct sockaddr *) addr, addrlen)) == -1 ) {
      perror("accept");
      exit(1);
   }
   else
      return connfd;
}
