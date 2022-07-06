//
// server.c
//

#include <stdlib.h>
#include <winsock2.h>
#include <stdio.h>

#define PORT            9000
#define MAX_MESSAGE_LEN 1023

int main(int argc, char *argv[])
{
  (void) argc;
  (void) argv;

	WSADATA wsa;

	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("WSAStartup failed: %d\n", WSAGetLastError());
		return EXIT_FAILURE;
	}

  SOCKET server;

	if ((server = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket: %d\n", WSAGetLastError());
    WSACleanup();
    return EXIT_FAILURE;
	}

  struct sockaddr_in server_addr;
	server_addr.sin_family = AF_INET;
	server_addr.sin_addr.s_addr = INADDR_ANY;
	server_addr.sin_port = htons(PORT);

	if (bind(server, (struct sockaddr *) &server_addr, sizeof(server_addr)) == SOCKET_ERROR)
	{
		printf("Bind failed: %d\n", WSAGetLastError());
    closesocket(server);
    WSACleanup();
    return EXIT_FAILURE;
	}

  if (listen(server, SOMAXCONN) == SOCKET_ERROR)
  {
    printf("Listen failed: %d\n", WSAGetLastError());
    closesocket(server);
    WSACleanup();
    return EXIT_FAILURE;
  }

  SOCKET client;
  struct sockaddr_in client_addr;
  int client_addr_len = sizeof(client_addr);
  char buffer[MAX_MESSAGE_LEN + 1];
  int nbytes;
  
  if ((client = accept(server, (struct sockaddr *) &client_addr, &client_addr_len)) == INVALID_SOCKET)
  {
    printf("Accept failed: %d\n", WSAGetLastError());
    closesocket(server);
    WSACleanup();
    return EXIT_FAILURE;
  }

  if ((nbytes = recv(client, buffer, MAX_MESSAGE_LEN, 0)) == SOCKET_ERROR)
  {
    printf("Receive failed: %d\n", WSAGetLastError());
    closesocket(client);
    closesocket(server);
    WSACleanup();
    return EXIT_FAILURE;
  }
  buffer[nbytes] = '\0';
  printf("Received: %s\n", buffer);

  if ((nbytes = send(client, buffer, nbytes, 0)) == SOCKET_ERROR)
  {
    printf("Send failed: %d\n", WSAGetLastError());
    closesocket(client);
    closesocket(server);
    WSACleanup();
    return EXIT_FAILURE;
  }
  printf("Sent: %s\n", buffer);

  closesocket(client);
  closesocket(server);
  WSACleanup();

  return EXIT_SUCCESS;
}
