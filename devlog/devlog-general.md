# 🎮 Devlog General

---

## 🌟 March 2025

### 🚀 Variable declaration

- Three way of variable declaration
- Curly brackets initialization is preferred (no narrowing)
- Parantheses initialization similar to curly brackets but it doesn't throw warning
- Assignment initialization (=) consider not safe if we must ensure the lossless accuracyi

### 🚀 Input Output

- there's several way of output in c++:
  - std::cerr used for printing and error
  - std::clog used for log messages
  - std::cout prints output in the console
- input using std:cin (space separated)

### 🚀 Boolean

- to output verbose true and false boolean value in c++, std::boolalpha used before prints it
- confused about how strcmp works:
  - strcmp compares 2 const char \*
  - if same, it returns 0, else return non-zero based on which one is greater

### 🚀 Outputted Format

- Using library iomanip and ios, I can format our output as I needs
- I can create table using std::setw and std::iosflags : left, right, internal
- Display its Dec, Hex, Oct form, decimal number after point, etc
- it's hard to track the last used flags etc, cause it works like an on/off switch rather than hold button

### 🚀 Pointer

- Pointer holds the address of another variable
- Raw pointer isn't safe
- Array holds the address of the first character
  - So, to access the second element we should do \*(array + 1)

### 🚀 Dynamic Memory Alloction

- There's two memory: stack and heap
- Heap has more space for memory allocation, but it quite complex
- Stack is the default memory allocation
- Using heap we can control when a memory dies
  - but this come with a catch, if we forget to kill it,
  - we ends up with garbage memory that can't be allocated or controlled by programmer

### 🚀 Dynamic Memory Alloction and Handles it

- We can create as much as memory needed as long we handle it properly
- Every time we delete a pointer we should assing the pointer into nullptr too
  - this would make our easier because we don't want some unexpected behaviour
- We maybe failed allocating a memory so std::nothrow comes in handy to catch this failed allocation
  - the allocated data becomes nullptr if it fails
