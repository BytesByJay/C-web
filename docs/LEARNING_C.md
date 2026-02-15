# C for Python Developers: The "Missing Manual"

Since you know Python, you already know *how to program*. You just need to translate that into C's world. Here is the Rosetta Stone for your project.

## 1. The Structure

*   **Python**: Scripts run from top to bottom.
*   **C**: The computer looks for a function specifically named `main()` and starts there.

## 2. Strings vs. Arrays

This is the biggest shock for Python developers.

*   **Python**: `message = "Hello"` is a high-level object. You can resize it, split it, join it.
*   **C**: There is no "String" type! "Hello" is just a **list of characters** sitting next to each other in memory.
    *   `char buffer[30000];`
    *   **Translation**: "Reserve a block of memory exactly 30,000 bytes long, and treat each byte as a character."
    *   **Why?** C gives you raw access to memory. Use `strlen()` to find the length, `strcpy()` to copy, etc.

## 3. Structs vs. Classes

Your project uses `struct Server`.

*   **Python Class**: Has data (`self.port`) AND methods (`def launch(self)`).
*   **C Struct**: Only has data. It's just a container.
    *   *Wait, but your struct has `launch`?*
    *   **The Trick**: Your struct creates a "slot" that can hold a **pointer to a function**. It says "I don't have a method, but I know the address of a function you can call."

## 4. Pointers (`*`) and Addresses (`&`)

This is the scary part, but think of it like this:

| Symbol | Name | Python Analogy | Example |
| :--- | :--- | :--- | :--- |
| `int x` | Variable | `x = 10` | A box holding the number 10. |
| `&x` | **Address** | `id(x)` | **Where** the box is in the room (e.g., Shelf A, Slot 1). |
| `int *p` | **Pointer** | Reference | A piece of paper with "Shelf A, Slot 1" written on it. |

**In your code:**
```c
server.launch(&server);
```
**Translation**: "Call the launch function, and as an argument, pass it the **address** of our server variable."
**Why?** Because C passes by value (copy). If you just passed `server`, C would make a xerox copy of the whole server. If the function changed something, it would only change the copy! Passing the *address* lets the function modify the *original*.

## 5. Your `test.c` Walkthrough

```c
// 1. HEADERS: Like 'import'
#include <stdio.h> 

// 2. FUNCTION: Defines what to do
void launch(struct Server *server) { 
    // ... logic ...
}

// 3. MAIN: The entry point
int main() {
    // 4. CONSTRUCTOR: Builds the struct
    struct Server server = server_constructor(...); 
    
    // 5. CALL: Starts the loop
    server.launch(&server); 
}
```
