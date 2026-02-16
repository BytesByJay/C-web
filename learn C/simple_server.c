/*
 * SIMPLE HTTP SERVER - LEARNING VERSION
 * 
 * This is a simplified version of your C-web server
 * with extensive comments to understand each step.
 * 
 * Compile: gcc -Wall -o simple_server simple_server.c
 * Run:     ./simple_server
 * Test:    curl http://localhost:8080/
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>

#define PORT 8080
#define BUFFER_SIZE 4096
#define BACKLOG 10

// Global server socket for cleanup
int server_socket = -1;

// Signal handler for graceful shutdown (Ctrl+C)
void handle_shutdown(int sig) {
    printf("\n\nShutting down server...\n");
    if (server_socket != -1) {
        close(server_socket);
    }
    exit(0);
}

// Parse the HTTP request path
// Example input: "GET /index.html HTTP/1.0"
// Returns: "/index.html"
char* parse_request_path(char *request) {
    static char path[256];
    char method[16], protocol[16];
    
    // Parse: METHOD PATH PROTOCOL
    if (sscanf(request, "%s %s %s", method, path, protocol) != 3) {
        return NULL;
    }
    
    printf("  Method: %s\n", method);
    printf("  Path: %s\n", path);
    printf("  Protocol: %s\n", protocol);
    
    return path;
}

// Get MIME type based on file extension
const char* get_mime_type(const char *path) {
    const char *ext = strrchr(path, '.');
    if (!ext) return "text/plain";
    
    if (strcmp(ext, ".html") == 0) return "text/html";
    if (strcmp(ext, ".css") == 0) return "text/css";
    if (strcmp(ext, ".js") == 0) return "application/javascript";
    if (strcmp(ext, ".jpg") == 0 || strcmp(ext, ".jpeg") == 0) return "image/jpeg";
    if (strcmp(ext, ".png") == 0) return "image/png";
    if (strcmp(ext, ".gif") == 0) return "image/gif";
    
    return "text/plain";
}

// Send HTTP response
void send_response(int client_socket, const char *status, const char *content_type, 
                   const char *body, int body_length) {
    char header[512];
    
    // Build HTTP response header
    snprintf(header, sizeof(header),
             "HTTP/1.0 %s\r\n"
             "Content-Type: %s\r\n"
             "Content-Length: %d\r\n"
             "Connection: close\r\n"
             "\r\n",
             status, content_type, body_length);
    
    // Send header
    write(client_socket, header, strlen(header));
    
    // Send body
    if (body && body_length > 0) {
        write(client_socket, body, body_length);
    }
}

// Serve a file
void serve_file(int client_socket, const char *filepath) {
    FILE *file = fopen(filepath, "rb");
    
    if (!file) {
        // 404 Not Found
        const char *body = "<h1>404 Not Found</h1>";
        send_response(client_socket, "404 Not Found", "text/html", 
                     body, strlen(body));
        printf("  Response: 404 Not Found\n");
        return;
    }
    
    // Get file size
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    
    // Read file into buffer
    char *content = malloc(file_size);
    if (!content) {
        fclose(file);
        const char *body = "<h1>500 Internal Server Error</h1>";
        send_response(client_socket, "500 Internal Server Error", "text/html",
                     body, strlen(body));
        return;
    }
    
    fread(content, 1, file_size, file);
    fclose(file);
    
    // Send response
    const char *mime_type = get_mime_type(filepath);
    send_response(client_socket, "200 OK", mime_type, content, file_size);
    printf("  Response: 200 OK (%ld bytes, %s)\n", file_size, mime_type);
    
    free(content);
}

// Handle client request
void handle_client(int client_socket) {
    char buffer[BUFFER_SIZE];
    
    // Read HTTP request
    int bytes_read = read(client_socket, buffer, BUFFER_SIZE - 1);
    if (bytes_read <= 0) {
        close(client_socket);
        return;
    }
    buffer[bytes_read] = '\0';
    
    printf("\n--- New Request ---\n");
    printf("Request:\n%s\n", buffer);
    
    // Parse request
    char *path = parse_request_path(buffer);
    if (!path) {
        const char *body = "<h1>400 Bad Request</h1>";
        send_response(client_socket, "400 Bad Request", "text/html",
                     body, strlen(body));
        close(client_socket);
        return;
    }
    
    // Build file path
    char filepath[512];
    if (strcmp(path, "/") == 0) {
        strcpy(filepath, "public/index.html");
    } else {
        snprintf(filepath, sizeof(filepath), "public%s", path);
    }
    
    // Serve file
    serve_file(client_socket, filepath);
    
    // Close connection
    close(client_socket);
}

// Main server loop
int main() {
    struct sockaddr_in server_addr, client_addr;
    socklen_t client_len = sizeof(client_addr);
    
    // Set up signal handler for Ctrl+C
    signal(SIGINT, handle_shutdown);
    
    printf("=== Simple HTTP Server ===\n\n");
    
    // STEP 1: Create socket
    printf("Step 1: Creating socket...\n");
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    if (server_socket == -1) {
        perror("socket() failed");
        return 1;
    }
    printf("  Socket created (fd: %d)\n", server_socket);
    
    // STEP 2: Set socket options (allow port reuse)
    printf("\nStep 2: Setting socket options...\n");
    int opt = 1;
    if (setsockopt(server_socket, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt)) == -1) {
        perror("setsockopt() failed");
        close(server_socket);
        return 1;
    }
    printf("  Socket options set (SO_REUSEADDR enabled)\n");
    
    // STEP 3: Configure server address
    printf("\nStep 3: Configuring server address...\n");
    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;           // IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;   // Accept from any IP
    server_addr.sin_port = htons(PORT);         // Port (host to network byte order)
    printf("  Address: 0.0.0.0:%d (INADDR_ANY)\n", PORT);
    
    // STEP 4: Bind socket to address
    printf("\nStep 4: Binding socket to address...\n");
    if (bind(server_socket, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("bind() failed");
        close(server_socket);
        return 1;
    }
    printf("  Socket bound to port %d\n", PORT);
    
    // STEP 5: Listen for connections
    printf("\nStep 5: Listening for connections...\n");
    if (listen(server_socket, BACKLOG) == -1) {
        perror("listen() failed");
        close(server_socket);
        return 1;
    }
    printf("  Listening with backlog of %d connections\n", BACKLOG);
    
    printf("\n=== Server is ready! ===\n");
    printf("Open your browser to: http://localhost:%d/\n", PORT);
    printf("Press Ctrl+C to stop the server.\n\n");
    
    // STEP 6: Accept and handle clients
    while (1) {
        printf("Waiting for connection...\n");
        
        // Accept incoming connection
        int client_socket = accept(server_socket, 
                                   (struct sockaddr*)&client_addr, 
                                   &client_len);
        
        if (client_socket == -1) {
            perror("accept() failed");
            continue;
        }
        
        // Get client IP address
        char client_ip[INET_ADDRSTRLEN];
        inet_ntop(AF_INET, &client_addr.sin_addr, client_ip, sizeof(client_ip));
        printf("Connection from: %s:%d\n", client_ip, ntohs(client_addr.sin_port));
        
        // Handle the client request
        handle_client(client_socket);
    }
    
    // Cleanup (never reached due to infinite loop)
    close(server_socket);
    return 0;
}

/*
 * UNDERSTANDING THE FLOW:
 * 
 * 1. socket()     - Creates a communication endpoint
 *                   Returns a file descriptor (integer)
 * 
 * 2. setsockopt() - Configures socket options
 *                   SO_REUSEADDR allows restarting server immediately
 * 
 * 3. bind()       - Associates socket with IP address and port
 *                   Like claiming "I'm listening on port 8080"
 * 
 * 4. listen()     - Marks socket as passive (ready to accept connections)
 *                   Creates a queue for incoming connections
 * 
 * 5. accept()     - Blocks until a client connects
 *                   Returns NEW socket for communication with that client
 * 
 * 6. read/write() - Communicate with client
 *                   read() receives data
 *                   write() sends data
 * 
 * 7. close()      - Closes the connection
 *                   Frees the file descriptor
 * 
 * 
 * PYTHON EQUIVALENT:
 * 
 * import socket
 * 
 * # 1. Create socket
 * server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
 * 
 * # 2. Set options
 * server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)
 * 
 * # 3. Bind
 * server.bind(('0.0.0.0', 8080))
 * 
 * # 4. Listen
 * server.listen(10)
 * 
 * while True:
 *     # 5. Accept
 *     client, addr = server.accept()
 *     print(f"Connection from {addr}")
 *     
 *     # 6. Read/Write
 *     data = client.recv(4096)
 *     client.send(b"HTTP/1.0 200 OK\r\n\r\nHello!")
 *     
 *     # 7. Close
 *     client.close()
 */
