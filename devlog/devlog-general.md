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

### 🚀 Character Manipulation

- There are so many things we can do in cstring lib
  - check is alphabetic using std::isalpha
  - check is alphanumeric using std::isalphanum
  - we can make it lowercase or uppercase by std::tolower or std::toupper
  - we can check is it blank string by using std:: std::isblank
  - etc
- By using strrchr, we can find the first occurence of character in a string
- All of this would be handy when it combine to something like std::transform, etc

### 🚀 Memory Leaks

- If a heap memory is changed the pointer without delete[] the heap first, it causes memory leaks
- This is bad because we don't want "unexpected" high memory usage in our program

### 🚀 Lambda function

- we can create function like we create variable using []()=>data_type_return{}
- this unlock the possibility to passing function as a parameter
- this is also useful when we only need a small function, but we must be careful cause I think this could reduce
  readability

### 🚀 Template function

- template function used when we need the same code but expected a multiple return value
- instead of overloading function with each data type
- we could just say template <typename T> then return T as the data_type. This would make our life easier
- if we need a specific data type should be handled differently, we could implement template specialization

### 🚀 SFML Shapes

- Learn how shapes are created and drawn to the RenderWindow
- Spawning shapes based on "cursor" circle shape
- Real time input using sf::Keybaord::isKeyPressed()
- Can't spawn shapes with some lifespan or spawning (bullet?)
- Need to remember the parameter used in every constructor of shapes

### 🚀 STL (Standard Template Library) Containers C++

- There are many containers in standar library, I learned that there mainly 3
  1. Key-Pairs Container => map and unordered-map
  2. In Out Behaviour => stack, queue, priority_queue
  3. Unique elements => set and unordered-set
- Unordered one seems to be faster lookup in general but doesn't guarantee the order or time needed
- there's also tuple that stores or combine multiple types in one object
- tuple used when returning multiple values from a function or any one time use data grouping
- next : mini-projects implementing stl containers

### 🚀 Student Database

- Using std::map and std::tuple to store NIM and Mahasiswa
- learn about std::optional for make parameter optional
- issues a lot need to be fix or implemented, but I focus on how to use std::map and other STL containers, so it's enough
- It's hard to track std::tuple because std::get doesn't have "semantic" way

### 🚀 SFML Mouse Input

- Learn how to handles mouse button events
- Displaying "particles" shapes
- Know that getGlobalBounds contains needs mapPixeltoCoords for better precision mouse input
- Using remove_if function to remove items from list

### 🚀 AABB Collision

- Learn about the AABB (Axis Aligned Bounding Box) Collision
- It check collision between entities by calculating the delta of its center position or origin position and find the overlap vector value of it
- After collision is detected, it should resolve how to handle the collision based on how the physics in our game engine behave.
- In this experiment, it pushes the moving object to the direction where it comes from by how deep is the overlap vector
