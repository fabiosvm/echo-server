//
// server.c
//

#include <stdlib.h>
#include <stdio.h>
#include "socket.h"

#define PORT            9000
#define MAX_MESSAGE_LEN 1023

int main(int argc, char *argv[])
{
  (void) argc;
  (void) argv;

	if (socket_startup() != 0)
	{
		printf("Socket startup failed: %d\n", socket_get_last_error());
		return EXIT_FAILURE;
	}

  socket_t server;

	if ((server = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket: %d\n", socket_get_last_error());
    socket_cleanup();
    return EXIT_FAILURE;
	}

  if (setsockopt(server, SOL_SOCKET, SO_REUSEADDR, &(int){1}, sizeof(int)) < 0)
  {
    printf("Could not set socket option: %d\n", socket_get_last_error());
    socket_cleanup();
    return EXIT_FAILURE;
  }
 
  struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);

	if (bind(server, (struct sockaddr *) &server_addr, sizeof(server_addr)) == SOCKET_ERROR)
	{
		printf("Bind failed: %d\n", socket_get_last_error());
    socket_close(server);
    socket_cleanup();
    return EXIT_FAILURE;
	}

  if (listen(server, SOMAXCONN) == SOCKET_ERROR)
  {
    printf("Listen failed: %d\n", socket_get_last_error());
    socket_close(server);
    socket_cleanup();
    return EXIT_FAILURE;
  }

  socket_t client;
  struct sockaddr_in client_addr;
  int client_addr_len = sizeof(client_addr);
  char buffer[MAX_MESSAGE_LEN + 1];
  int nbytes;
  
  if ((client = accept(server, (struct sockaddr *) &client_addr, &client_addr_len)) == INVALID_SOCKET)
  {
    printf("Accept failed: %d\n", socket_get_last_error());
    socket_close(server);
    socket_cleanup();
    return EXIT_FAILURE;
  }

  if ((nbytes = recv(client, buffer, MAX_MESSAGE_LEN, 0)) == SOCKET_ERROR)
  {
    printf("Receive failed: %d\n", socket_get_last_error());
    socket_close(client);
    socket_close(server);
    socket_cleanup();
    return EXIT_FAILURE;
  }
  buffer[nbytes] = '\0';
  printf("Received: %s\n", buffer);

  if ((nbytes = send(client, buffer, nbytes, 0)) == SOCKET_ERROR)
  {
    printf("Send failed: %d\n", socket_get_last_error());
    socket_close(client);
    socket_close(server);
    socket_cleanup();
    return EXIT_FAILURE;
  }
  printf("Sent: %s\n", buffer);

  socket_close(client);
  socket_close(server);
  socket_cleanup();

  return EXIT_SUCCESS;
}
