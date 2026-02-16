# C Programming Exercises
## Progressive Learning Path

---

## Exercise 1: Hello, Variables!

### Goal
Understand basic types, variables, and printf formatting.

### Task
Create a program that:
1. Declares variables of different types (int, float, char, char[])
2. Prints them with proper format specifiers
3. Shows the size of each type using sizeof()

### Starter Code
```c
#include <stdio.h>

int main() {
    // TODO: Declare variables
    int age = 25;
    // Add more...
    
    // TODO: Print them
    printf("Age: %d\n", age);
    // Add more...
    
    // TODO: Show sizes
    printf("Size of int: %zu bytes\n", sizeof(int));
    // Add more...
    
    return 0;
}
```

### Expected Output
```
Age: 25
Height: 5.9
Initial: A
Name: Alice
Size of int: 4 bytes
Size of float: 4 bytes
...
```

---

## Exercise 2: Array Reverser

### Goal
Practice array manipulation and pointer arithmetic.

### Task
Write a function that reverses an array in-place.

### Starter Code
```c
#include <stdio.h>

void reverse(int *arr, int size) {
    // TODO: Implement reversal
    // Hint: Use two pointers, one at start, one at end
    // Swap them and move towards center
}

void print_array(int *arr, int size) {
    for (int i = 0; i < size; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

int main() {
    int arr[] = {1, 2, 3, 4, 5};
    int size = sizeof(arr) / sizeof(arr[0]);
    
    printf("Before: ");
    print_array(arr, size);
    
    reverse(arr, size);
    
    printf("After:  ");
    print_array(arr, size);
    
    return 0;
}
```

### Solution
```c
void reverse(int *arr, int size) {
    int *start = arr;
    int *end = arr + size - 1;
    
    while (start < end) {
        // Swap
        int temp = *start;
        *start = *end;
        *end = temp;
        
        // Move pointers
        start++;
        end--;
    }
}
```

---

## Exercise 3: String Length

### Goal
Understand how strings work in C (null-terminated character arrays).

### Task
Implement your own strlen() function without using the standard library.

### Starter Code
```c
#include <stdio.h>

int my_strlen(const char *str) {
    // TODO: Count characters until '\0'
    return 0;
}

int main() {
    char *test = "Hello, World!";
    printf("Length of '%s': %d\n", test, my_strlen(test));
    return 0;
}
```

### Solution
```c
int my_strlen(const char *str) {
    int count = 0;
    while (str[count] != '\0') {
        count++;
    }
    return count;
    
    // Alternative using pointers:
    // const char *start = str;
    // while (*str != '\0') str++;
    // return str - start;
}
```

---

## Exercise 4: Dynamic Array

### Goal
Practice memory allocation and creating dynamic data structures.

### Task
Create a simple dynamic array (vector) that can grow.

### Starter Code
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *data;
    int size;
    int capacity;
} Vector;

Vector* vector_create(int initial_capacity) {
    // TODO: Allocate Vector
    // TODO: Allocate data array
    // TODO: Initialize size and capacity
    return NULL;
}

void vector_push(Vector *v, int value) {
    // TODO: Check if resize needed
    // TODO: Add element
    // TODO: Increment size
}

int vector_get(Vector *v, int index) {
    // TODO: Bounds checking
    // TODO: Return element
    return 0;
}

void vector_free(Vector *v) {
    // TODO: Free data
    // TODO: Free vector
}

int main() {
    Vector *v = vector_create(2);
    
    vector_push(v, 10);
    vector_push(v, 20);
    vector_push(v, 30);  // Should trigger resize
    
    for (int i = 0; i < v->size; i++) {
        printf("%d ", vector_get(v, i));
    }
    printf("\n");
    
    vector_free(v);
    return 0;
}
```

### Solution
```c
Vector* vector_create(int initial_capacity) {
    Vector *v = malloc(sizeof(Vector));
    if (!v) return NULL;
    
    v->data = malloc(sizeof(int) * initial_capacity);
    if (!v->data) {
        free(v);
        return NULL;
    }
    
    v->size = 0;
    v->capacity = initial_capacity;
    return v;
}

void vector_push(Vector *v, int value) {
    if (v->size >= v->capacity) {
        // Resize needed
        int new_capacity = v->capacity * 2;
        int *new_data = realloc(v->data, sizeof(int) * new_capacity);
        if (!new_data) return;  // Handle error properly in real code
        
        v->data = new_data;
        v->capacity = new_capacity;
    }
    
    v->data[v->size] = value;
    v->size++;
}

int vector_get(Vector *v, int index) {
    if (index < 0 || index >= v->size) {
        fprintf(stderr, "Index out of bounds\n");
        return -1;
    }
    return v->data[index];
}

void vector_free(Vector *v) {
    if (v) {
        free(v->data);
        free(v);
    }
}
```

---

## Exercise 5: File Word Counter

### Goal
Practice file I/O and string manipulation.

### Task
Create a program that counts words in a text file (like `wc -w`).

### Starter Code
```c
#include <stdio.h>
#include <ctype.h>

int count_words(const char *filename) {
    // TODO: Open file
    // TODO: Read character by character
    // TODO: Count transitions from space to non-space
    // TODO: Close file
    return 0;
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <filename>\n", argv[0]);
        return 1;
    }
    
    int words = count_words(argv[1]);
    printf("Word count: %d\n", words);
    
    return 0;
}
```

### Solution
```c
int count_words(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        perror("Error opening file");
        return -1;
    }
    
    int words = 0;
    int in_word = 0;
    int c;
    
    while ((c = fgetc(file)) != EOF) {
        if (isspace(c)) {
            in_word = 0;
        } else {
            if (!in_word) {
                words++;
                in_word = 1;
            }
        }
    }
    
    fclose(file);
    return words;
}
```

---

## Exercise 6: Simple Linked List

### Goal
Understand pointers and dynamic data structures.

### Task
Implement basic linked list operations.

### Starter Code
```c
#include <stdio.h>
#include <stdlib.h>

typedef struct Node {
    int data;
    struct Node *next;
} Node;

Node* create_node(int data) {
    // TODO: Allocate node
    // TODO: Set data and next
    return NULL;
}

void insert_front(Node **head, int data) {
    // TODO: Create new node
    // TODO: Point new node to current head
    // TODO: Update head
}

void print_list(Node *head) {
    // TODO: Traverse and print
}

void free_list(Node *head) {
    // TODO: Free all nodes
}

int main() {
    Node *list = NULL;
    
    insert_front(&list, 3);
    insert_front(&list, 2);
    insert_front(&list, 1);
    
    print_list(list);  // Should print: 1 -> 2 -> 3 -> NULL
    
    free_list(list);
    return 0;
}
```

### Solution
```c
Node* create_node(int data) {
    Node *node = malloc(sizeof(Node));
    if (!node) return NULL;
    
    node->data = data;
    node->next = NULL;
    return node;
}

void insert_front(Node **head, int data) {
    Node *new_node = create_node(data);
    if (!new_node) return;
    
    new_node->next = *head;
    *head = new_node;
}

void print_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
}

void free_list(Node *head) {
    Node *current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}
```

---

## Exercise 7: TCP Echo Client

### Goal
Learn network programming basics.

### Task
Create a TCP client that connects to a server and echoes messages.

### Starter Code
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define PORT 8080
#define BUFFER_SIZE 1024

int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    
    // TODO: Create socket
    
    // TODO: Configure server address
    
    // TODO: Connect to server
    
    // TODO: Send and receive data
    
    // TODO: Close socket
    
    return 0;
}
```

### Solution
```c
int main() {
    int sock;
    struct sockaddr_in server_addr;
    char buffer[BUFFER_SIZE];
    
    // Create socket
    sock = socket(AF_INET, SOCK_STREAM, 0);
    if (sock == -1) {
        perror("socket");
        return 1;
    }
    
    // Configure server address
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    inet_pton(AF_INET, "127.0.0.1", &server_addr.sin_addr);
    
    // Connect
    if (connect(sock, (struct sockaddr*)&server_addr, sizeof(server_addr)) == -1) {
        perror("connect");
        close(sock);
        return 1;
    }
    
    printf("Connected to server. Type messages (Ctrl+D to quit):\n");
    
    // Send and receive
    while (fgets(buffer, BUFFER_SIZE, stdin) != NULL) {
        // Send message
        write(sock, buffer, strlen(buffer));
        
        // Receive echo
        int bytes = read(sock, buffer, BUFFER_SIZE - 1);
        if (bytes <= 0) break;
        
        buffer[bytes] = '\0';
        printf("Server: %s", buffer);
    }
    
    close(sock);
    return 0;
}
```

---

## Exercise 8: Mini HTTP Parser

### Goal
Understand how to parse text protocols.

### Task
Parse HTTP request line and headers.

### Starter Code
```c
#include <stdio.h>
#include <string.h>

typedef struct {
    char method[16];
    char path[256];
    char version[16];
} HttpRequest;

int parse_request_line(const char *line, HttpRequest *req) {
    // TODO: Parse "GET /index.html HTTP/1.0"
    // Hint: Use sscanf
    return 0;
}

int main() {
    const char *request = 
        "GET /index.html HTTP/1.0\r\n"
        "Host: localhost\r\n"
        "User-Agent: MyBrowser/1.0\r\n"
        "\r\n";
    
    HttpRequest req;
    
    // Parse first line
    char *newline = strchr(request, '\r');
    if (newline) {
        char line[256];
        strncpy(line, request, newline - request);
        line[newline - request] = '\0';
        
        if (parse_request_line(line, &req)) {
            printf("Method: %s\n", req.method);
            printf("Path: %s\n", req.path);
            printf("Version: %s\n", req.version);
        }
    }
    
    return 0;
}
```

### Solution
```c
int parse_request_line(const char *line, HttpRequest *req) {
    if (sscanf(line, "%s %s %s", req->method, req->path, req->version) == 3) {
        return 1;
    }
    return 0;
}
```

---

## Progressive Challenges

### Week 1-2: Basics
1. Calculator with all operations
2. Temperature converter (C to F and vice versa)
3. Array sorter (bubble sort)
4. String reverser and palindrome checker

### Week 3-4: Pointers & Memory
5. Implement strcat, strcmp, strcpy
6. Matrix multiplication
7. Dynamic string builder
8. Simple memory pool allocator

### Week 5-6: Data Structures
9. Stack implementation
10. Queue implementation
11. Binary search tree
12. Hash table

### Week 7-8: File & System
13. File copy utility
14. Directory lister
15. Log file parser
16. CSV reader/writer

### Week 9-10: Networking
17. TCP echo server
18. Simple HTTP server
19. Chat server (multi-client)
20. File transfer protocol

---

## Debugging Tips

### Using GDB
```bash
# Compile with debug symbols
gcc -g -o program program.c

# Run with debugger
gdb ./program

# Common commands:
break main        # Set breakpoint
run              # Start program
next             # Next line
step             # Step into function
print variable   # Print value
backtrace        # Show call stack
continue         # Continue execution
```

### Valgrind for Memory Issues
```bash
# Check for memory leaks
valgrind --leak-check=full ./program

# Check for invalid memory access
valgrind --track-origins=yes ./program
```

### Common Compiler Warnings
```bash
# Enable all warnings
gcc -Wall -Wextra -pedantic program.c
```

---

## Testing Your Knowledge

After completing these exercises, you should be able to:

✅ Understand memory layout (stack vs heap)
✅ Work confidently with pointers
✅ Manage dynamic memory (malloc/free)
✅ Implement basic data structures
✅ Do file I/O
✅ Create network programs
✅ Debug segmentation faults
✅ Read and modify existing C code

---

## Next Steps

1. **Read the C-Web source code** - You now have the foundation to understand it!
2. **Extend C-Web** - Add features like:
   - POST request handling
   - URL routing
   - Basic authentication
   - File uploads
3. **Build your own projects**:
   - Command-line tools
   - Game (terminal-based)
   - Database engine
   - Shell

Good luck! 🚀
