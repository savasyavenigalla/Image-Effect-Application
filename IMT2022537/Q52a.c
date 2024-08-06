/*
Question :

Concurrent Server Creation: Write a program to create a concurrent server:
a. Use fork
b. Use pthread_create

Explanation: 


*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <string.h>

#define MAX_NUM_CLIENTS 5
#define PORT 3001

// this handles all the client connections
void *handle_client(void *arg)
{   
    // receives socket descriptor as argument(client connection)
    int cli = *(int *)arg;
    char buffer[500];

    // Read data from the client
    ssize_t num_bytes = read(cli, buffer, sizeof(buffer) - 1);
    if (num_bytes > 0)
    {
        buffer[num_bytes] = '\0';
        printf("Received data from client: %s\n", buffer);

        const char *response = "Response from the server."; // Responding to the client
        write(cli, response, strlen(response));
    }

    // Close the client socket
    close(cli);

    pthread_exit(NULL);
}

int main()
{
    int serv, cli; // Socket descriptors for server and client
    struct sockaddr_in address;
    int addrlen = sizeof(address);

    // Create the server socket
    if ((serv = socket(AF_INET, SOCK_STREAM, 0)) == 0)
    {
        perror("socket failed");
        exit(EXIT_FAILURE);
    }

    // Set up server address structure
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    // Bind the socket to the specified address and port
    if (bind(serv, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Failed to bind");
        exit(EXIT_FAILURE);
    }

    // Listen for incoming connections on the server socket
    if (listen(serv, MAX_NUM_CLIENTS) < 0)
    {
        perror("Failed to listen");
        exit(EXIT_FAILURE);
    }

    pthread_t client_threads[MAX_NUM_CLIENTS]; // Array to hold client thread IDs
    int clients = 0;

    // Accept incoming connections and create threads to handle them
    while (1)
    {
        // Accept a client connection
        if ((cli = accept(serv, (struct sockaddr *)&address, (socklen_t *)&addrlen)) < 0)
        {
            perror("accept failed");
            exit(EXIT_FAILURE);
        }

        // Create a thread to handle the client connection
        if (cli != -1)
        {
            pthread_create(&client_threads[clients], NULL, handle_client, &cli);
            clients++;

            // Wait for all client threads to finish before accepting more connections
            if (clients >= MAX_NUM_CLIENTS)
            {
                for (int i = 0; i < clients; i++)
                {
                    pthread_join(client_threads[i], NULL);
                }
                clients = 0;
            }
        }
    }

    return 0;
}
