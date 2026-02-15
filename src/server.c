
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include "Server.h"

// Function to get content type based on file extension
char* get_content_type(const char* path) {
    const char* ext = strrchr(path, '.');
    if (!ext) return "text/plain";
    
    if (strcmp(ext, ".html") == 0) return "text/html";
    if (strcmp(ext, ".css") == 0) return "text/css";
    if (strcmp(ext, ".js") == 0) return "application/javascript";
    if (strcmp(ext, ".json") == 0) return "application/json";
    if (strcmp(ext, ".png") == 0) return "image/png";
    if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) return "image/jpeg";
    if (strcmp(ext, ".gif") == 0) return "image/gif";
    if (strcmp(ext, ".svg") == 0) return "image/svg+xml";
    if (strcmp(ext, ".ico") == 0) return "image/x-icon";
    
    return "text/plain";
}

// Read file content into memory
char* read_file(const char* filepath, long* file_size) {
    FILE* file = fopen(filepath, "rb");
    if (!file) {
        return NULL;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    *file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Allocate memory and read file
    char* content = (char*)malloc(*file_size);
    if (!content) {
        fclose(file);
        return NULL;
    }
    
    fread(content, 1, *file_size, file);
    fclose(file);
    
    return content;
}

// Parse the requested path from HTTP request
char* parse_request_path(const char* request) {
    // Find "GET " in the request
    const char* start = strstr(request, "GET ");
    if (!start) return NULL;
    
    start += 4; // Skip "GET "
    
    // Find the space after the path
    const char* end = strchr(start, ' ');
    if (!end) return NULL;
    
    // Extract path
    int len = end - start;
    char* path = (char*)malloc(len + 1);
    strncpy(path, start, len);
    path[len] = '\0';
    
    return path;
}

// Send 404 Not Found response
void send_404(int socket) {
    char* response = "HTTP/1.1 404 Not Found\r\n"
                     "Content-Type: text/html\r\n"
                     "Content-Length: 47\r\n"
                     "\r\n"
                     "<h1>404 Not Found</h1><p>File not found.</p>";
    
    write(socket, response, strlen(response));
}

// In Python, this would be a method like: def launch(self):
void launch(struct Server *server)
{
    char buffer[30000]; // This is like 'buffer = ""' but with a fixed size limit
    printf("====== WAITING FOR CONNECTIONS ======\n");
    printf("Server running at http://localhost:%d/\n", server->port);
    printf("Serving files from: ./public/\n");
    fflush(stdout);
    
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
        fflush(stdout);

        // Read the request from the browser (client)
        memset(buffer, 0, sizeof(buffer)); // Clear buffer
        read(new_socket, buffer, 30000);
        printf("%s\n", buffer); // Print the request to the terminal
        fflush(stdout);

        // Parse the requested path
        char* request_path = parse_request_path(buffer);
        
        if (request_path) {
            // Handle root path
            if (strcmp(request_path, "/") == 0) {
                free(request_path);
                request_path = strdup("/index.html");
            }
            
            // Build file path (public/ + request_path)
            char filepath[512];
            snprintf(filepath, sizeof(filepath), "./public%s", request_path);
            
            printf("Requesting: %s (File: %s)\n", request_path, filepath);
            fflush(stdout);
            
            // Read the file
            long file_size;
            char* file_content = read_file(filepath, &file_size);
            
            if (file_content) {
                // File found - send 200 OK
                char* content_type = get_content_type(filepath);
                
                // Build HTTP headers
                char headers[512];
                int header_len = snprintf(headers, sizeof(headers),
                    "HTTP/1.1 200 OK\r\n"
                    "Content-Type: %s\r\n"
                    "Content-Length: %ld\r\n"
                    "\r\n",
                    content_type, file_size);
                
                // Send headers
                write(new_socket, headers, header_len);
                
                // Send file content
                write(new_socket, file_content, file_size);
                
                free(file_content);
                printf("Sent: %s (%ld bytes)\n", filepath, file_size);
            } else {
                // File not found - send 404
                send_404(new_socket);
                printf("404: %s not found\n", filepath);
            }
            
            free(request_path);
        } else {
            // Invalid request
            send_404(new_socket);
        }
        
        // Hang up the phone
        close(new_socket);
        printf("Connection closed.\n\n");
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