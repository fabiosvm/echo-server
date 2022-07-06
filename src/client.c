//
// client.c
//

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "socket.h"

#define HOST           "127.0.0.1"
#define PORT            9000
#define MESSAGE        "Hi!"
#define MAX_MESSAGE_LEN 1023

int main(int argc, char *argv[])
{
  (void) argc;
  (void) argv;

  if (socket_startup())
  {
    printf("Socket startup failed: %d\n", socket_get_last_error());
    return EXIT_FAILURE;
  }

  socket_t client;

  if ((client = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
  {
    printf("Could not create socket: %d\n", socket_get_last_error());
    socket_cleanup();
    return EXIT_FAILURE;
  }

  struct sockaddr_in server_addr;
  memset(&server_addr, 0, sizeof(server_addr));
  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);
  server_addr.sin_addr.s_addr = inet_addr(HOST);

  if (connect(client, (struct sockaddr *) &server_addr, sizeof(server_addr)) == SOCKET_ERROR)
  {
    printf("Connect failed: %d\n", socket_get_last_error());
    socket_close(client);
    socket_cleanup();
    return EXIT_FAILURE;
  }

  char buffer[MAX_MESSAGE_LEN + 1];
  int nbytes;

  strncpy(buffer, MESSAGE, MAX_MESSAGE_LEN);
  nbytes = strlen(buffer);

  if ((nbytes = socket_send(client, buffer, nbytes, 0)) == SOCKET_ERROR)
  {
    printf("Send failed: %d\n", socket_get_last_error());
    socket_close(client);
    socket_cleanup();
    return EXIT_FAILURE;
  }
  printf("Sent %s\n", buffer);

  if ((nbytes = socket_recv(client, buffer, MAX_MESSAGE_LEN, 0)) == SOCKET_ERROR)
  {
    printf("Recv failed: %d\n", socket_get_last_error());
    socket_close(client);
    socket_cleanup();
    return EXIT_FAILURE;
  }
  buffer[nbytes] = '\0';
  printf("Received: %s\n", buffer);

  socket_close(client);
  socket_cleanup();

  return EXIT_SUCCESS;
}
