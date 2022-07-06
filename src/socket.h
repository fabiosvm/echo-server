//
// socket.h
//

#ifndef SOCKET_H
#define SOCKET_H

#ifdef _WIN32
  #include <winsock2.h>
#else
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <unistd.h>
#endif

#ifdef _WIN32
  #define socket_t SOCKET
#else
  #define socket_t       int
  #define INVALID_SOCKET -1
  #define SOCKET_ERROR   -1
#endif

int socket_startup(void);
int socket_cleanup(void);
int socket_get_last_error(void);
int socket_close(socket_t sock);

#endif // SOCKET_H
