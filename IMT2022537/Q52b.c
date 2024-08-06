/*
Question :

Concurrent Server Creation: Write a program to create a concurrent server:
a. Use fork
b. Use pthread_create

Explanation:


*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>

#define PORT 3001

int main()
{
    int client_fd;                     // Socket descriptor for the client
    struct sockaddr_in server_address; // Structure to hold server address information
    char message[256];                 // Buffer to store message to be sent to the server

    // Create the client socket
    if ((client_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address structure
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(PORT);

    // Connect to the server
    if (connect(client_fd, (struct sockaddr *)&server_address, sizeof(server_address)) < 0)
    {
        perror("connect failed");
        exit(EXIT_FAILURE);
    }

    // Prompt the user for a message to send
    printf("Enter a message to send to the server: ");
    fgets(message, sizeof(message), stdin);

    // Send the message to the server
    if (write(client_fd, message, strlen(message)) < 0)
    {
        perror("write failed");
        exit(EXIT_FAILURE);
    }

    // Read the response from the server
    char buffer[256]; // Buffer to store server response
    ssize_t num_bytes = read(client_fd, buffer, sizeof(buffer) - 1);
    if (num_bytes > 0)
    {
        buffer[num_bytes] = '\0';
        printf("Server response: %s\n", buffer);
    }

    // Close the client socket
    close(client_fd);

    return 0;
}
