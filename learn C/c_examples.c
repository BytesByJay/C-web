/*
 * PRACTICAL C EXAMPLES
 * Compile each section individually to practice
 */

// =============================================================================
// EXAMPLE 1: MEMORY VISUALIZATION
// Compile: gcc -o memory memory_demo.c
// =============================================================================

#include <stdio.h>
#include <stdlib.h>

void memory_demo() {
    printf("=== MEMORY DEMO ===\n\n");
    
    // Stack variables
    int stack_var = 42;
    int stack_array[5] = {1, 2, 3, 4, 5};
    
    // Heap variable
    int *heap_var = malloc(sizeof(int));
    *heap_var = 100;
    
    // Print addresses
    printf("Stack variable address: %p, value: %d\n", (void*)&stack_var, stack_var);
    printf("Stack array address:    %p\n", (void*)stack_array);
    printf("Heap variable address:  %p, value: %d\n", (void*)heap_var, *heap_var);
    
    // Show memory layout
    printf("\nMemory addresses (lower numbers = lower in memory):\n");
    printf("Heap typically starts at:  ~0x... (varies)\n");
    printf("Stack typically starts at: ~0x7fff... (high addresses)\n");
    
    free(heap_var);
}

// =============================================================================
// EXAMPLE 2: POINTER PRACTICE
// =============================================================================

void pointer_demo() {
    printf("\n=== POINTER DEMO ===\n\n");
    
    int x = 10;
    int *ptr = &x;
    int **ptr_to_ptr = &ptr;
    
    printf("Value of x: %d\n", x);
    printf("Address of x: %p\n", (void*)&x);
    printf("\n");
    printf("Value of ptr (address of x): %p\n", (void*)ptr);
    printf("Value at ptr (*ptr): %d\n", *ptr);
    printf("Address of ptr itself: %p\n", (void*)&ptr);
    printf("\n");
    printf("Value of ptr_to_ptr (address of ptr): %p\n", (void*)ptr_to_ptr);
    printf("Value at ptr_to_ptr (**ptr_to_ptr): %d\n", **ptr_to_ptr);
    
    // Modify through double pointer
    **ptr_to_ptr = 20;
    printf("\nAfter modifying through double pointer:\n");
    printf("x = %d\n", x);
}

// =============================================================================
// EXAMPLE 3: ARRAY AND POINTER ARITHMETIC
// =============================================================================

void array_demo() {
    printf("\n=== ARRAY DEMO ===\n\n");
    
    int arr[5] = {10, 20, 30, 40, 50};
    int *ptr = arr;
    
    printf("Array elements using array notation:\n");
    for (int i = 0; i < 5; i++) {
        printf("arr[%d] = %d (address: %p)\n", i, arr[i], (void*)&arr[i]);
    }
    
    printf("\nArray elements using pointer arithmetic:\n");
    for (int i = 0; i < 5; i++) {
        printf("*(ptr + %d) = %d (address: %p)\n", i, *(ptr + i), (void*)(ptr + i));
    }
    
    printf("\nNotice: arr[i] is the same as *(arr + i)\n");
    printf("Address difference: %ld bytes\n", (char*)&arr[1] - (char*)&arr[0]);
}

// =============================================================================
// EXAMPLE 4: STRING MANIPULATION
// =============================================================================

void string_demo() {
    printf("\n=== STRING DEMO ===\n\n");
    
    // String literal (read-only)
    char *literal = "Hello";
    printf("String literal: %s\n", literal);
    
    // Modifiable string on stack
    char stack_str[] = "World";
    printf("Stack string before: %s\n", stack_str);
    stack_str[0] = 'w';
    printf("Stack string after:  %s\n", stack_str);
    
    // Dynamic string on heap
    char *heap_str = malloc(20);
    if (heap_str == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    strcpy(heap_str, "Dynamic");
    printf("Heap string: %s\n", heap_str);
    
    // String iteration
    printf("\nCharacter by character:\n");
    for (int i = 0; heap_str[i] != '\0'; i++) {
        printf("heap_str[%d] = '%c' (ASCII: %d)\n", i, heap_str[i], heap_str[i]);
    }
    
    free(heap_str);
}

// =============================================================================
// EXAMPLE 5: STRUCTS AND FUNCTION POINTERS
// =============================================================================

typedef struct {
    char name[50];
    int age;
    void (*print)(struct Person *self);
} Person;

void person_print(Person *self) {
    printf("Name: %s, Age: %d\n", self->name, self->age);
}

void struct_demo() {
    printf("\n=== STRUCT DEMO ===\n\n");
    
    // Stack-allocated struct
    Person p1;
    strcpy(p1.name, "Alice");
    p1.age = 30;
    p1.print = person_print;
    
    printf("Person 1: ");
    p1.print(&p1);
    
    // Heap-allocated struct
    Person *p2 = malloc(sizeof(Person));
    if (p2 == NULL) {
        printf("Memory allocation failed!\n");
        return;
    }
    strcpy(p2->name, "Bob");
    p2->age = 25;
    p2->print = person_print;
    
    printf("Person 2: ");
    p2->print(p2);
    
    free(p2);
}

// =============================================================================
// EXAMPLE 6: LINKED LIST
// =============================================================================

typedef struct Node {
    int data;
    struct Node *next;
} Node;

void linked_list_demo() {
    printf("\n=== LINKED LIST DEMO ===\n\n");
    
    // Create nodes
    Node *head = malloc(sizeof(Node));
    head->data = 1;
    head->next = malloc(sizeof(Node));
    head->next->data = 2;
    head->next->next = malloc(sizeof(Node));
    head->next->next->data = 3;
    head->next->next->next = NULL;
    
    // Traverse
    printf("Linked list: ");
    Node *current = head;
    while (current != NULL) {
        printf("%d -> ", current->data);
        current = current->next;
    }
    printf("NULL\n");
    
    // Free memory
    current = head;
    while (current != NULL) {
        Node *temp = current;
        current = current->next;
        free(temp);
    }
}

// =============================================================================
// EXAMPLE 7: FILE I/O
// =============================================================================

void file_demo() {
    printf("\n=== FILE I/O DEMO ===\n\n");
    
    // Write to file
    FILE *fp = fopen("test.txt", "w");
    if (fp == NULL) {
        perror("Error opening file for writing");
        return;
    }
    fprintf(fp, "Hello, File!\n");
    fprintf(fp, "Number: %d\n", 42);
    fclose(fp);
    printf("Data written to test.txt\n");
    
    // Read from file
    fp = fopen("test.txt", "r");
    if (fp == NULL) {
        perror("Error opening file for reading");
        return;
    }
    
    printf("Reading from test.txt:\n");
    char buffer[256];
    while (fgets(buffer, sizeof(buffer), fp) != NULL) {
        printf("  %s", buffer);
    }
    fclose(fp);
}

// =============================================================================
// EXAMPLE 8: COMMON BUGS
// =============================================================================

void bug_demo() {
    printf("\n=== COMMON BUGS (COMMENTED OUT) ===\n\n");
    
    // BUG 1: Memory leak
    printf("Bug 1: Memory Leak\n");
    /*
    for (int i = 0; i < 1000; i++) {
        int *leak = malloc(sizeof(int) * 1000);
        // Oops! Never freed
    }
    */
    printf("  (Code commented - would leak memory)\n");
    
    // BUG 2: Use after free
    printf("\nBug 2: Use After Free\n");
    /*
    int *ptr = malloc(sizeof(int));
    *ptr = 42;
    free(ptr);
    printf("%d\n", *ptr);  // Accessing freed memory!
    */
    printf("  (Code commented - would be undefined behavior)\n");
    
    // BUG 3: Buffer overflow
    printf("\nBug 3: Buffer Overflow\n");
    /*
    char buffer[5];
    strcpy(buffer, "This is too long!");  // Overflow!
    */
    printf("  (Code commented - would overflow buffer)\n");
    
    // BUG 4: Returning pointer to stack variable
    printf("\nBug 4: Returning Pointer to Local Variable\n");
    printf("  (See commented function below)\n");
    /*
    int* bad_function() {
        int local = 42;
        return &local;  // local is destroyed after return!
    }
    */
}

// =============================================================================
// MAIN FUNCTION
// =============================================================================

int main() {
    printf("C LEARNING EXAMPLES\n");
    printf("===================\n");
    
    memory_demo();
    pointer_demo();
    array_demo();
    string_demo();
    struct_demo();
    linked_list_demo();
    file_demo();
    bug_demo();
    
    printf("\n=== ALL DEMOS COMPLETE ===\n");
    return 0;
}
