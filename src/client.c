//
// client.c
//

#include <stdlib.h>
#include <winsock2.h>
#include <stdio.h>
#include <string.h>

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

  SOCKET client;

  if ((client = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
  {
    printf("Could not create socket: %d\n", WSAGetLastError());
    WSACleanup();
    return EXIT_FAILURE;
  }

  struct sockaddr_in server_addr;
  server_addr.sin_family = AF_INET;
  server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
  server_addr.sin_port = htons(PORT);

  if (connect(client, (struct sockaddr *) &server_addr, sizeof(server_addr)) == SOCKET_ERROR)
  {
    printf("Connect failed: %d\n", WSAGetLastError());
    closesocket(client);
    WSACleanup();
    return EXIT_FAILURE;
  }

  char buffer[MAX_MESSAGE_LEN + 1];
  int nbytes;

  strncpy(buffer, "Hi!", MAX_MESSAGE_LEN);
  nbytes = strlen(buffer);

  if ((nbytes = send(client, buffer, nbytes, 0)) == SOCKET_ERROR)
  {
    printf("Send failed: %d\n", WSAGetLastError());
    closesocket(client);
    WSACleanup();
    return EXIT_FAILURE;
  }
  printf("Sent %s\n", buffer);

  if ((nbytes = recv(client, buffer, MAX_MESSAGE_LEN, 0)) == SOCKET_ERROR)
  {
    printf("Recv failed: %d\n", WSAGetLastError());
    closesocket(client);
    WSACleanup();
    return EXIT_FAILURE;
  }
  buffer[nbytes] = '\0';
  printf("Received: %s\n", buffer);

  closesocket(client);
  WSACleanup();

  return EXIT_SUCCESS;
}
