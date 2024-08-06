/*
Question :
51. Inter-Machine Communication using Socket: Write a program to communicate between
two machines using sockets


*/

#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

int main()
{
    struct sockaddr_in serv;
    int sd = socket(AF_INET, SOCK_STREAM, 0); // sock_stream for tcp socket type, o for default protocol
    //sd stores the file discriptor value
    if (sd == -1)
    {
        perror("Error: ");
        return -1;
    }

    int portno = 5557;
    serv.sin_family = AF_INET;
    serv.sin_addr.s_addr = INADDR_ANY;// available interface
    serv.sin_port = htons(portno);
    // establish a connection to the server using socket descriptor-sd and server address-serv
    if (connect(sd, (struct sockaddr *)&serv, sizeof(serv)) != -1)
    {   
        //data transmission
        write(sd, "Hello", sizeof("Hello")); // send the message to the server
        char buf[100];
        // receive data 
        read(sd, buf, sizeof(buf));
        printf("Acknowledgment from server: %s\n", buf);
    }
    else
    {
        printf("Unsuccessful connection.\n");
        perror("");
    }

    close(sd);
}