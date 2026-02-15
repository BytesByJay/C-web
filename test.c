

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include "Server.h"

// In Python, this would be a method like: def launch(self):
void launch(struct Server *server)
{
    char buffer[30000]; // This is like 'buffer = ""' but with a fixed size limit
    printf("====== WAITING FOR CONNECTIONS ======\n");
    
    // while True:
    while(1)
    {
        int address_length = sizeof(server->address);
        
        // This line pauses the program until a client connects!
        // It returns a 'new_socket' which is a handle to talk to THAT specific client.
        int new_socket = accept(server->socket, (struct sockaddr *)&server->address, (socklen_t *)&address_length);
        
        if (new_socket < 0)
        {
            perror("Failed to accept connection");
            continue;
        }
        
        printf("Connection accepted!\n");
        fflush(stdout); // Force the log to show up immediately

        // Read the request from the browser (client)
        // buffer.read(new_socket)
        read(new_socket, buffer, 30000);
        printf("%s\n", buffer); // Print the request to the terminal
        fflush(stdout);

        // The response we want to send back (HTTP headers + Body)
        // correct HTTP requires \r\n line endings!
        char *hello = "HTTP/1.1 200 OK\r\nDate: Sun, 10 Oct 2021 20:26:00 GMT\r\nServer: Apache/2.2.14 (Win32)\r\nContent-Length: 12\r\nContent-Type: text/html\r\n\r\nHello world!";

        // Send the response
        write(new_socket, hello, strlen(hello));
        
        // Hang up the phone
        close(new_socket);
        printf("Connection closed.\r\n");
        fflush(stdout);
    }
}

int main()
{
    // Creating the server object (like: server = Server(...))
    // We pass 'launch' as a function pointer - telling the server "Run this function when you start"
    struct Server server = server_constructor(AF_INET, SOCK_STREAM, 0, INADDR_ANY, 9999, 10, launch);
    
    // Start the server (like: server.launch())
    server.launch(&server);
}