# Learning C: A Complete Guide for Python Developers
## From High-Level to Low-Level Programming

---

## Table of Contents
1. [Why C? Understanding the Low Level](#why-c)
2. [Chapter 1: The Fundamentals](#chapter-1-fundamentals)
3. [Chapter 2: Memory - The Core Difference](#chapter-2-memory)
4. [Chapter 3: Pointers - C's Superpower](#chapter-3-pointers)
5. [Chapter 4: Strings and Arrays](#chapter-4-strings-arrays)
6. [Chapter 5: Structs and Data Structures](#chapter-5-structs)
7. [Chapter 6: File I/O and System Calls](#chapter-6-file-io)
8. [Chapter 7: Network Programming](#chapter-7-networking)
9. [Chapter 8: Building Real Projects](#chapter-8-projects)
10. [Practice Exercises](#exercises)

---

## Why C? Understanding the Low Level {#why-c}

### What Python Hides From You

```python
# Python
x = [1, 2, 3]
y = x
y.append(4)
print(x)  # [1, 2, 3, 4] - Wait, what?
```

**What's really happening:**
- Memory allocation (where does the list live?)
- Reference counting (when does memory get freed?)
- Dynamic typing (how does Python know it's a list?)
- Garbage collection (who cleans up?)

**In C, YOU control all of this.**

### The Abstraction Pyramid

```
Python/JavaScript  ← You are here
    ↓
C/C++             ← We're going here
    ↓
Assembly
    ↓
Machine Code
    ↓
Hardware
```

---

## Chapter 1: The Fundamentals {#chapter-1-fundamentals}

### 1.1 Your First C Program

```c
#include <stdio.h>

int main() {
    printf("Hello, World!\n");
    return 0;
}
```

**vs Python:**
```python
print("Hello, World!")
```

### Breaking it down:

**`#include <stdio.h>`**
- Like Python's `import`, but it literally copies code into your file
- `stdio.h` = "Standard Input/Output Header"
- Contains declarations for `printf`, `scanf`, etc.

**`int main()`**
- Every C program starts here (unlike Python which runs top-to-bottom)
- `int` means it returns an integer
- Return 0 = success, non-zero = error

**`printf()`**
- Function to print formatted text
- `\n` = newline (not automatic like Python's print)

**`return 0;`**
- Exit code for the operating system
- Semicolons are REQUIRED (not optional like JS)

### 1.2 Compilation vs Interpretation

**Python (interpreted):**
```bash
python script.py  # Runs directly
```

**C (compiled):**
```bash
gcc program.c -o program  # Compile first
./program                 # Then run
```

**What happens during compilation:**
1. **Preprocessing**: Expands #include, #define
2. **Compilation**: Converts to assembly
3. **Assembly**: Converts to machine code
4. **Linking**: Combines with libraries

### 1.3 Data Types - Size Matters!

```c
// Python
x = 5           # int (unlimited size!)
y = 3.14        # float
name = "Alice"  # str

// C - You must declare types AND sizes matter!
int x = 5;              // 4 bytes (usually), range: -2^31 to 2^31-1
float y = 3.14;         // 4 bytes, less precise
double z = 3.14159;     // 8 bytes, more precise
char letter = 'A';      // 1 byte, single character
char name[] = "Alice";  // Array of chars (string)

// Unsigned versions (only positive)
unsigned int count = 100;  // 0 to 2^32-1
```

**Checking sizes:**
```c
#include <stdio.h>

int main() {
    printf("int: %zu bytes\n", sizeof(int));
    printf("float: %zu bytes\n", sizeof(float));
    printf("double: %zu bytes\n", sizeof(double));
    printf("char: %zu bytes\n", sizeof(char));
    printf("pointer: %zu bytes\n", sizeof(void*));
    return 0;
}
```

### 1.4 Variables and Constants

```c
// Variables
int age = 25;
age = 26;  // Can change

// Constants
const int MAX_USERS = 100;
// MAX_USERS = 200;  // ERROR! Cannot change

// #define (preprocessor macro)
#define PI 3.14159
// Literally replaces PI with 3.14159 before compilation
```

### 1.5 Operators

```c
// Arithmetic (same as Python)
int a = 10 + 5;   // 15
int b = 10 - 5;   // 5
int c = 10 * 5;   // 50
int d = 10 / 5;   // 2
int e = 10 % 3;   // 1 (modulo/remainder)

// Integer division!
int x = 7 / 2;    // 2 (not 3.5!)
float y = 7.0 / 2;  // 3.5

// Increment/Decrement
int i = 5;
i++;    // i = 6 (post-increment)
++i;    // i = 7 (pre-increment)
i--;    // i = 6 (decrement)

// Compound operators
i += 5;  // i = i + 5
i *= 2;  // i = i * 2
```

### 1.6 Control Flow

```c
// if-else (similar to Python, but with parentheses and braces)
if (x > 10) {
    printf("Greater\n");
} else if (x == 10) {
    printf("Equal\n");
} else {
    printf("Less\n");
}

// while loop
int i = 0;
while (i < 5) {
    printf("%d\n", i);
    i++;
}

// for loop (different syntax!)
for (int i = 0; i < 5; i++) {
    printf("%d\n", i);
}
// Equivalent Python: for i in range(5):

// do-while (runs at least once)
int count = 0;
do {
    printf("%d\n", count);
    count++;
} while (count < 5);

// switch statement (like match in Python 3.10+)
int day = 2;
switch (day) {
    case 1:
        printf("Monday\n");
        break;  // Important! Without break, it falls through
    case 2:
        printf("Tuesday\n");
        break;
    default:
        printf("Other day\n");
}
```

---

## Chapter 2: Memory - The Core Difference {#chapter-2-memory}

### 2.1 Understanding Computer Memory

```
Memory Layout of a C Program:

HIGH ADDRESSES
┌─────────────────┐
│  Command Line   │  Arguments and environment variables
│  & Environment  │
├─────────────────┤
│                 │
│     STACK       │  Local variables, function calls
│       ↓         │  Grows downward
│                 │
├─────────────────┤
│                 │
│       ↑         │
│     HEAP        │  Dynamic memory (malloc)
│                 │  Grows upward
├─────────────────┤
│  Uninitialized  │  Global/static variables (BSS)
│      Data       │
├─────────────────┤
│  Initialized    │  Global/static initialized variables
│      Data       │
├─────────────────┤
│   Text/Code     │  Your compiled program code
│   (Read-only)   │
└─────────────────┘
LOW ADDRESSES
```

### 2.2 Stack vs Heap

**STACK:**
```c
void function() {
    int x = 5;        // Allocated on stack
    int arr[100];     // Allocated on stack
    // When function returns, this memory is AUTOMATICALLY freed!
}
```

**Characteristics:**
- Fast allocation/deallocation
- Limited size (~1-8 MB typically)
- Automatic cleanup
- LIFO (Last In, First Out)

**HEAP:**
```c
void function() {
    int *ptr = malloc(sizeof(int) * 100);  // Allocated on heap
    // Use the memory...
    free(ptr);  // YOU must free it manually!
    // If you forget to free() = MEMORY LEAK!
}
```

**Characteristics:**
- Slower allocation
- Large size (limited by available RAM)
- Manual management
- Memory persists until you free() it

### 2.3 Python vs C Memory Model

```python
# Python - everything is on the heap, managed for you
def python_function():
    x = [1, 2, 3]      # Allocated on heap
    return x           # Returns reference
    # Garbage collector frees it later when no references exist

result = python_function()
# x is still accessible via result
```

```c
// C - you choose stack or heap
int* c_function() {
    int x = 5;         // Stack - DESTROYED after return!
    return &x;         // DANGER! Returning pointer to dead memory!
}

int* safe_function() {
    int *x = malloc(sizeof(int));  // Heap - persists!
    *x = 5;
    return x;          // Safe - but caller must free()!
}

// Usage
int *result = safe_function();
printf("%d\n", *result);
free(result);  // Clean up!
```

### 2.4 Memory Allocation

```c
#include <stdlib.h>  // for malloc, free

// Allocate single integer
int *num = malloc(sizeof(int));
if (num == NULL) {
    // Allocation failed!
    return 1;
}
*num = 42;
free(num);

// Allocate array
int *array = malloc(sizeof(int) * 10);  // 10 integers
if (array == NULL) {
    return 1;
}
for (int i = 0; i < 10; i++) {
    array[i] = i * 2;
}
free(array);

// calloc - allocates and zeros memory
int *zeros = calloc(10, sizeof(int));  // All zeros
free(zeros);

// realloc - resize existing allocation
int *arr = malloc(sizeof(int) * 5);
arr = realloc(arr, sizeof(int) * 10);  // Now 10 elements
free(arr);
```

### 2.5 Common Memory Errors

**1. Memory Leak:**
```c
void leak() {
    int *ptr = malloc(sizeof(int) * 100);
    // ... use ptr ...
    // Oops, forgot to free()!
}  // Memory is lost forever (until program exits)
```

**2. Use After Free:**
```c
int *ptr = malloc(sizeof(int));
*ptr = 42;
free(ptr);
printf("%d\n", *ptr);  // UNDEFINED BEHAVIOR! Dangling pointer
```

**3. Double Free:**
```c
int *ptr = malloc(sizeof(int));
free(ptr);
free(ptr);  // CRASH! Freeing same memory twice
```

**4. Buffer Overflow:**
```c
int arr[5];
arr[10] = 42;  // DANGER! Writing beyond array bounds
```

---

## Chapter 3: Pointers - C's Superpower {#chapter-3-pointers}

### 3.1 What is a Pointer?

**A pointer is a variable that stores a memory address.**

```c
int x = 42;       // Normal variable
int *ptr = &x;    // Pointer to x

// Memory visualization:
// Address    Variable    Value
// 0x1000     x          42
// 0x2000     ptr        0x1000  (address of x)
```

### 3.2 Pointer Operators

```c
int x = 42;

// & (address-of operator)
int *ptr = &x;    // ptr now holds the address of x

// * (dereference operator)
int value = *ptr;  // Gets value at address (42)
*ptr = 100;        // Changes value at address
// Now x is 100!

printf("Value of x: %d\n", x);           // 100
printf("Address of x: %p\n", (void*)&x); // 0x1000 (example)
printf("Value of ptr: %p\n", (void*)ptr);// 0x1000
printf("Value at ptr: %d\n", *ptr);      // 100
```

### 3.3 Pointer Arithmetic

```c
int arr[5] = {10, 20, 30, 40, 50};
int *ptr = arr;  // Points to first element

printf("%d\n", *ptr);      // 10
printf("%d\n", *(ptr+1));  // 20
printf("%d\n", *(ptr+2));  // 30

// ptr+1 doesn't add 1 byte, it adds sizeof(int) bytes!
// If int is 4 bytes:
// ptr+0 = address 0x1000 → value 10
// ptr+1 = address 0x1004 → value 20
// ptr+2 = address 0x1008 → value 30

// Array notation is just pointer arithmetic!
arr[2] == *(arr + 2)  // Both access third element
```

### 3.4 Pointers to Pointers

```c
int x = 42;
int *ptr = &x;        // Pointer to int
int **ptr2 = &ptr;    // Pointer to pointer to int

// Memory:
// x     = 42
// ptr   = address of x
// ptr2  = address of ptr

printf("%d\n", x);      // 42
printf("%d\n", *ptr);   // 42
printf("%d\n", **ptr2); // 42

// Modifying through double pointer
**ptr2 = 100;
printf("%d\n", x);      // 100
```

### 3.5 Pointers and Functions

**Pass by Value (Python default for primitives):**
```c
void change(int x) {
    x = 100;  // Only changes local copy
}

int main() {
    int num = 5;
    change(num);
    printf("%d\n", num);  // Still 5!
}
```

**Pass by Pointer (like Python lists/dicts):**
```c
void change(int *x) {
    *x = 100;  // Changes original!
}

int main() {
    int num = 5;
    change(&num);  // Pass address
    printf("%d\n", num);  // 100!
}
```

**Returning Multiple Values:**
```c
// Python
def get_stats():
    return 10, 20, 30

min_val, max_val, avg = get_stats()

// C - using pointers
void get_stats(int *min, int *max, int *avg) {
    *min = 10;
    *max = 20;
    *avg = 30;
}

int main() {
    int min, max, avg;
    get_stats(&min, &max, &avg);
    printf("Min: %d, Max: %d, Avg: %d\n", min, max, avg);
}
```

### 3.6 NULL Pointers

```c
int *ptr = NULL;  // Points to nothing (address 0)

if (ptr == NULL) {
    printf("Pointer is null\n");
}

// ALWAYS check before dereferencing!
if (ptr != NULL) {
    printf("%d\n", *ptr);
}

// Common pattern
int *data = malloc(sizeof(int) * 100);
if (data == NULL) {
    fprintf(stderr, "Memory allocation failed!\n");
    return 1;
}
// Use data...
free(data);
data = NULL;  // Good practice to null after freeing
```

### 3.7 Function Pointers

```c
// Define a function
int add(int a, int b) {
    return a + b;
}

int subtract(int a, int b) {
    return a - b;
}

// Pointer to function
int (*operation)(int, int);

operation = add;
printf("%d\n", operation(5, 3));  // 8

operation = subtract;
printf("%d\n", operation(5, 3));  // 2

// Python equivalent
def add(a, b):
    return a + b

operation = add  # Just assign the function
print(operation(5, 3))
```

---

## Chapter 4: Strings and Arrays {#chapter-4-strings-arrays}

### 4.1 Arrays

```c
// Static array (size known at compile time)
int numbers[5];           // Uninitialized (garbage values)
int nums[5] = {1, 2, 3};  // Partially initialized (rest are 0)
int arr[] = {1, 2, 3, 4}; // Size inferred

// Accessing
printf("%d\n", arr[0]);  // 1
arr[2] = 100;

// Array size
int size = sizeof(arr) / sizeof(arr[0]);  // 4

// Multi-dimensional arrays
int matrix[3][4];  // 3 rows, 4 columns
matrix[0][0] = 1;
matrix[2][3] = 99;

// Dynamic array (heap)
int *dynamic = malloc(sizeof(int) * 10);
dynamic[0] = 42;
free(dynamic);
```

### 4.2 Strings in C (Character Arrays)

**The Truth: C has NO string type!**

```c
// String is just an array of characters ending with '\0'
char str[6] = "Hello";  // Actually: {'H','e','l','l','o','\0'}

// String literal (read-only, in code section)
char *str2 = "World";   // Pointer to read-only memory
// str2[0] = 'w';  // CRASH! Can't modify string literals

// Modifiable string
char str3[] = "Hello";  // Copies to stack
str3[0] = 'h';          // OK!

// The null terminator '\0' is CRUCIAL
char bad[5] = {'H', 'e', 'l', 'l', 'o'};  // NO '\0'!
printf("%s\n", bad);  // UNDEFINED BEHAVIOR!
```

### 4.3 String Functions

```c
#include <string.h>

char str1[50] = "Hello";
char str2[] = "World";

// Length
int len = strlen(str1);  // 5 (doesn't count '\0')

// Copy
strcpy(str1, "Goodbye");  // str1 is now "Goodbye"
strncpy(str1, "Hi", 2);   // Safer - limits copy length

// Concatenate
strcat(str1, " World");   // str1 is now "Goodbye World"
strncat(str1, "!", 1);    // Safer version

// Compare
if (strcmp(str1, str2) == 0) {
    printf("Strings are equal\n");
}

// Search
char *pos = strchr(str1, 'o');  // Find first 'o'
char *word = strstr(str1, "World");  // Find substring
```

### 4.4 String Buffer Overflows (Common Bug!)

```c
// DANGER!
char buffer[5];
strcpy(buffer, "Hello World");  // OVERFLOW! "Hello World" needs 12 bytes
// Writes beyond buffer, corrupting memory!

// SAFE VERSION
char buffer[20];
strncpy(buffer, "Hello World", sizeof(buffer) - 1);
buffer[sizeof(buffer) - 1] = '\0';  // Ensure null termination

// Or use snprintf
char buffer[20];
snprintf(buffer, sizeof(buffer), "Hello %s", "World");
```

### 4.5 Dynamic Strings

```c
// Allocate string on heap
char *str = malloc(100);  // 100 bytes
if (str == NULL) return 1;

strcpy(str, "Dynamic string");
printf("%s\n", str);
free(str);

// Reading user input
char input[100];
printf("Enter text: ");
fgets(input, sizeof(input), stdin);  // Safe input
// Remove newline
input[strcspn(input, "\n")] = '\0';
```

---

## Chapter 5: Structs and Data Structures {#chapter-5-structs}

### 5.1 Structs (Like Python Classes but Simpler)

```c
// Define a struct
struct Person {
    char name[50];
    int age;
    float height;
};

// Create and use
struct Person p1;
strcpy(p1.name, "Alice");
p1.age = 30;
p1.height = 5.6;

// Initialize at creation
struct Person p2 = {"Bob", 25, 5.9};

// Array of structs
struct Person people[10];
people[0] = p1;

// Pointer to struct
struct Person *ptr = &p1;
ptr->age = 31;  // Arrow operator for pointers
// Equivalent to: (*ptr).age = 31;
```

### 5.2 typedef (Making Life Easier)

```c
// Without typedef
struct Person p1;

// With typedef
typedef struct {
    char name[50];
    int age;
} Person;

Person p2;  // Cleaner! No need for 'struct' keyword
```

### 5.3 Dynamic Structs

```c
typedef struct {
    char *name;
    int age;
} Person;

// Allocate struct on heap
Person *p = malloc(sizeof(Person));
if (p == NULL) return 1;

p->name = malloc(50);
strcpy(p->name, "Charlie");
p->age = 40;

// Clean up
free(p->name);
free(p);
```

### 5.4 Linked Lists

```c
typedef struct Node {
    int data;
    struct Node *next;  // Pointer to next node
} Node;

// Create nodes
Node *head = malloc(sizeof(Node));
head->data = 1;
head->next = malloc(sizeof(Node));
head->next->data = 2;
head->next->next = NULL;

// Traverse
Node *current = head;
while (current != NULL) {
    printf("%d\n", current->data);
    current = current->next;
}

// Free list
current = head;
while (current != NULL) {
    Node *temp = current;
    current = current->next;
    free(temp);
}
```

### 5.5 Your Server.h Struct Explained

```c
struct Server {
    // Configuration
    int domain;      // AF_INET (IPv4)
    int service;     // SOCK_STREAM (TCP)
    int protocol;    // 0 (default)
    u_long interface;// IP address
    int port;        // Port number
    int backlog;     // Connection queue size
    
    // Runtime state
    int socket;                    // File descriptor
    struct sockaddr_in address;    // Socket address
    
    // Behavior
    void (*launch)(struct Server *server);  // Function pointer
};
```

**This is essentially:**
```python
class Server:
    def __init__(self, domain, service, protocol, interface, port, backlog, launch):
        # Configuration
        self.domain = domain
        self.service = service
        # ... etc
        
        # Runtime
        self.socket = socket.socket(domain, service, protocol)
        self.address = (interface, port)
        
        # Behavior
        self.launch = launch  # Callback function
```

---

## Chapter 6: File I/O and System Calls {#chapter-6-file-io}

### 6.1 Standard I/O (Buffered)

```c
#include <stdio.h>

// Writing to file
FILE *fp = fopen("data.txt", "w");
if (fp == NULL) {
    perror("Error opening file");
    return 1;
}
fprintf(fp, "Hello, File!\n");
fprintf(fp, "Number: %d\n", 42);
fclose(fp);

// Reading from file
FILE *fp2 = fopen("data.txt", "r");
char buffer[256];
while (fgets(buffer, sizeof(buffer), fp2) != NULL) {
    printf("%s", buffer);
}
fclose(fp2);

// Binary files
FILE *bin = fopen("data.bin", "wb");
int nums[] = {1, 2, 3, 4, 5};
fwrite(nums, sizeof(int), 5, bin);
fclose(bin);
```

### 6.2 System Calls (Unbuffered, Lower Level)

```c
#include <fcntl.h>
#include <unistd.h>

// Open file (returns file descriptor)
int fd = open("data.txt", O_WRONLY | O_CREAT, 0644);
if (fd == -1) {
    perror("open");
    return 1;
}

// Write
char *msg = "Hello, System Call!";
write(fd, msg, strlen(msg));

// Close
close(fd);

// Read
fd = open("data.txt", O_RDONLY);
char buffer[100];
int bytes_read = read(fd, buffer, sizeof(buffer) - 1);
buffer[bytes_read] = '\0';
printf("%s\n", buffer);
close(fd);
```

### 6.3 File Descriptor Table

```
Every process has a file descriptor table:

FD 0: STDIN  (keyboard input)
FD 1: STDOUT (terminal output)
FD 2: STDERR (error output)
FD 3+: Your opened files
```

```c
// Writing to stdout directly
write(1, "Hello\n", 6);

// Writing to stderr
write(2, "Error!\n", 7);

// This is what printf() does internally!
```

---

## Chapter 7: Network Programming {#chapter-7-networking}

### 7.1 Socket Basics

**Socket = endpoint for network communication**

```c
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

// Create socket
int sock = socket(AF_INET, SOCK_STREAM, 0);
// AF_INET   = IPv4
// SOCK_STREAM = TCP (reliable, ordered)
// 0         = Default protocol

if (sock == -1) {
    perror("socket");
    return 1;
}
```

### 7.2 Server Socket Flow

```c
// 1. Create socket
int server_fd = socket(AF_INET, SOCK_STREAM, 0);

// 2. Set socket options (allow port reuse)
int opt = 1;
setsockopt(server_fd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

// 3. Configure address
struct sockaddr_in address;
address.sin_family = AF_INET;
address.sin_addr.s_addr = INADDR_ANY;  // Accept from any IP
address.sin_port = htons(8080);        // Port 8080

// 4. Bind socket to address
bind(server_fd, (struct sockaddr*)&address, sizeof(address));

// 5. Listen for connections
listen(server_fd, 10);  // Queue up to 10 connections

// 6. Accept client connections
int client_fd = accept(server_fd, NULL, NULL);

// 7. Read/Write data
char buffer[1024];
int bytes = read(client_fd, buffer, sizeof(buffer));
write(client_fd, "HTTP/1.0 200 OK\r\n\r\nHello!", 24);

// 8. Close connections
close(client_fd);
close(server_fd);
```

### 7.3 Client Socket Flow

```c
// 1. Create socket
int sock = socket(AF_INET, SOCK_STREAM, 0);

// 2. Configure server address
struct sockaddr_in server;
server.sin_family = AF_INET;
server.sin_port = htons(8080);
inet_pton(AF_INET, "127.0.0.1", &server.sin_addr);

// 3. Connect to server
connect(sock, (struct sockaddr*)&server, sizeof(server));

// 4. Send data
write(sock, "GET / HTTP/1.0\r\n\r\n", 18);

// 5. Receive response
char buffer[4096];
int bytes = read(sock, buffer, sizeof(buffer));
buffer[bytes] = '\0';
printf("%s\n", buffer);

// 6. Close
close(sock);
```

### 7.4 Understanding Your C-Web Server

```c
// This is what your server_constructor does:

1. socket()     → Creates communication endpoint
2. setsockopt() → Configure socket (reuse address)
3. bind()       → Assign address (IP + port)
4. listen()     → Start listening for connections
5. accept()     → Accept incoming client (in launch function)
6. read/write() → Communicate with client
7. close()      → Clean up
```

**Python equivalent:**
```python
import socket

# 1. Create socket
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)

# 2. Set options
server.setsockopt(socket.SOL_SOCKET, socket.SO_REUSEADDR, 1)

# 3. Bind to address
server.bind(('0.0.0.0', 8080))

# 4. Listen
server.listen(10)

while True:
    # 5. Accept client
    client, addr = server.accept()
    
    # 6. Communicate
    data = client.recv(1024)
    client.send(b"HTTP/1.0 200 OK\r\n\r\nHello!")
    
    # 7. Close client
    client.close()
```

---

## Chapter 8: Building Real Projects {#chapter-8-projects}

### 8.1 Project: Simple HTTP Server

**Understanding HTTP:**
```
Request:
GET /index.html HTTP/1.0
Host: localhost
[blank line]

Response:
HTTP/1.0 200 OK
Content-Type: text/html
Content-Length: 13
[blank line]
Hello, World!
```

**Basic Implementation:**
```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define PORT 8080
#define BUFFER_SIZE 4096

int main() {
    int server_fd, client_fd;
    struct sockaddr_in address;
    char buffer[BUFFER_SIZE];
    
    // Create socket
    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    
    // Configure address
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);
    
    // Bind and listen
    bind(server_fd, (struct sockaddr*)&address, sizeof(address));
    listen(server_fd, 10);
    
    printf("Server listening on port %d\n", PORT);
    
    while (1) {
        // Accept client
        client_fd = accept(server_fd, NULL, NULL);
        
        // Read request
        int bytes = read(client_fd, buffer, BUFFER_SIZE - 1);
        buffer[bytes] = '\0';
        printf("Request:\n%s\n", buffer);
        
        // Send response
        char *response = 
            "HTTP/1.0 200 OK\r\n"
            "Content-Type: text/html\r\n"
            "\r\n"
            "<h1>Hello from C!</h1>";
        
        write(client_fd, response, strlen(response));
        close(client_fd);
    }
    
    close(server_fd);
    return 0;
}
```

### 8.2 Compilation and Debugging

```bash
# Compile with debugging symbols
gcc -g -Wall -Wextra server.c -o server

# Run with debugger
gdb ./server

# GDB commands:
# break main       - Set breakpoint
# run              - Start program
# next             - Next line
# step             - Step into function
# print variable   - Print value
# continue         - Continue execution
# quit             - Exit

# Memory debugging with valgrind
valgrind --leak-check=full ./server

# Compile with optimizations (release)
gcc -O2 -Wall server.c -o server
```

### 8.3 Common Build Tools

**Makefile:**
```makefile
CC = gcc
CFLAGS = -Wall -Wextra -g
SRC = src/server.c src/http.c
OBJ = $(SRC:.c=.o)
TARGET = bin/server

all: $(TARGET)

$(TARGET): $(OBJ)
    $(CC) $(CFLAGS) -o $@ $^

%.o: %.c
    $(CC) $(CFLAGS) -c $< -o $@

clean:
    rm -f $(OBJ) $(TARGET)

run: $(TARGET)
    ./$(TARGET)
```

```bash
# Build
make

# Clean and rebuild
make clean all

# Run
make run
```

---

## Practice Exercises {#exercises}

### Beginner Level

**1. Calculator:**
```c
// Create a calculator that:
// - Takes two numbers and an operator (+, -, *, /)
// - Performs the operation
// - Handles division by zero
```

**2. String Reverser:**
```c
// Write a function to reverse a string in-place
void reverse(char *str) {
    // Your code here
}
```

**3. Array Statistics:**
```c
// Find min, max, and average of an array
void stats(int *arr, int size, int *min, int *max, float *avg) {
    // Your code here
}
```

### Intermediate Level

**4. Dynamic Array (Vector):**
```c
typedef struct {
    int *data;
    int size;
    int capacity;
} Vector;

Vector* vector_create();
void vector_push(Vector *v, int value);
int vector_get(Vector *v, int index);
void vector_free(Vector *v);
```

**5. File Line Counter:**
```c
// Count lines, words, and characters in a file
// Like 'wc' command in Unix
```

**6. Simple Key-Value Store:**
```c
// Implement a hash map with:
// - put(key, value)
// - get(key)
// - delete(key)
```

### Advanced Level

**7. Multi-threaded Server:**
```c
// Modify the HTTP server to handle multiple clients using threads
#include <pthread.h>

void* handle_client(void* arg) {
    int client_fd = *(int*)arg;
    // Handle request
    close(client_fd);
    return NULL;
}
```

**8. Memory Allocator:**
```c
// Implement your own malloc() and free()
// Understanding how memory management works
```

**9. Extend C-Web:**
- Add support for different HTTP methods (POST, PUT, DELETE)
- Implement URL routing
- Add basic authentication
- Support file uploads

---

## Key Takeaways

### Python vs C - Core Differences

| Aspect | Python | C |
|--------|--------|---|
| Memory | Automatic (GC) | Manual (malloc/free) |
| Types | Dynamic | Static |
| Strings | First-class objects | Character arrays |
| Arrays | Lists (dynamic) | Fixed size |
| Compilation | Interpreted | Compiled |
| Speed | Slower | Much faster |
| Safety | Safe (exceptions) | Unsafe (crashes) |
| Abstraction | High-level | Low-level |

### When to Use C

✅ **Use C when you need:**
- Maximum performance
- Direct hardware access
- Operating system development
- Embedded systems
- Understanding how things work

❌ **Don't use C when:**
- Rapid prototyping needed
- Memory safety is critical
- You need complex data structures
- Python/Go/Rust would suffice

### Learning Path

1. **Weeks 1-2:** Basics (syntax, types, control flow)
2. **Weeks 3-4:** Memory and pointers
3. **Weeks 5-6:** Data structures
4. **Weeks 7-8:** File I/O and system calls
5. **Weeks 9-10:** Network programming
6. **Weeks 11-12:** Build real projects

### Resources

**Books:**
- "The C Programming Language" by K&R (classic)
- "C Programming: A Modern Approach" by K.N. King
- "Effective C" by Robert C. Seacord

**Online:**
- [Beej's Guide to Network Programming](https://beej.us/guide/bgnet/)
- [Learn C](https://www.learn-c.org/)
- [CS50 - Harvard's C course](https://cs50.harvard.edu/)

**Practice:**
- [LeetCode](https://leetcode.com/) in C
- [Project Euler](https://projecteuler.net/)
- Build your own Unix tools (cat, grep, ls)

---

## Final Notes

C is **not** a language you learn in a week. It takes time to:
- Understand memory management
- Debug segmentation faults
- Master pointers
- Think in a systems-oriented way

But once you understand C, you'll understand:
- How Python works under the hood
- Why garbage collection is needed
- What your OS is doing
- How networks actually work
- The real cost of abstractions

**You're not just learning a language - you're learning how computers actually work.**

Good luck on your journey! 🚀
