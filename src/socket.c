//
// socket.c
//

#include "socket.h"

#ifndef _WIN32
  #include <errno.h>
#endif

int socket_startup(void)
{
#ifdef _WIN32
  WSADATA wsa;
  return WSAStartup(MAKEWORD(2, 2), &wsa);
#else
  return 0;
#endif
}

int socket_cleanup(void)
{
#ifdef _WIN32
  return WSACleanup();
#else
  return 0;
#endif
}

int socket_get_last_error(void)
{
#ifdef _WIN32
  return WSAGetLastError();
#else
  return errno;
#endif
}

int socket_close(socket_t sock)
{
  int status = 0;
  #ifdef _WIN32
    status = shutdown(sock, SD_BOTH);
    status = (!status) ? closesocket(sock) : status;
  #else
    status = shutdown(sock, SHUT_RDWR);
    status = (!status) ? close(sock) : status;
  #endif
  return status;
}
