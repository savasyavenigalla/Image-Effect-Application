/*
Question :
51. Inter-Machine Communication using Socket: Write a program to communicate between
two machines using sockets


*/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>

int main()
{   
    // two structs serv for servor and cli for client
    struct sockaddr_in serv, cli;
    int portno = 5557;

    int sd = socket(AF_INET, SOCK_STREAM, 0);
    if (sd == -1)
    {
        perror("Error: ");
        return -1;
    }
    serv.sin_family = AF_INET;  //address family
    serv.sin_addr.s_addr = INADDR_ANY;//accept connections on any ip address
    serv.sin_port = htons(portno);

    // set values to reuse the address and port. helps to restart the serve automatically
    int opt = 1;
    if (setsockopt(sd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)))
    {
        perror("Error: ");
        return -1;
    }
    // associate the socket with ip and port number
    if (bind(sd, (struct sockaddr *)&serv, sizeof(serv)) == -1)
    {
        perror("Bind error:\n");
        return -1;
    }
    // put socket in listen state to allow for incomin connections
        if (listen(sd, 100) == -1)
    {
        perror("Listen erro:\n");
        return -1;
    }

    printf("Listening.\n");
    int nsd;
    char buf[100];
    int size = sizeof(cli);
    // to continuously accept connections
    while (1)
    {
        printf("Do you want to accept(1) or leave(2)?\n");
        int ch;
        scanf("%d", &ch);
        if (ch == 2)
        {
            close(sd);
            printf("Exiting\n");
            return 0;
        }
        nsd = accept(sd, (struct sockaddr *)&cli, &size);
        read(nsd, &buf, sizeof(buf));
        printf("Message from client: %s\n", buf);
        char *message = "Received";
        sleep(5);
        write(nsd, message, sizeof(message));
        getchar();
        close(nsd);
    }
    close(sd);
}