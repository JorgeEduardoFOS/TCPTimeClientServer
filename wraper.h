#include <stdio.h>//FILE
#include <netdb.h>//sockaddr, socklen_t

int Socket(int domain, int type, int protocol);
void Bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Inet_pton(int af, const char *restrict src, void *restrict dst);
void Connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
void Listen(int sockfd, int backlog);
void Fputs(const char *restrict s, FILE *restrict fluxo);
int Accept(int sockfd, struct sockaddr *restrict addr, socklen_t *restrict addrlen);
