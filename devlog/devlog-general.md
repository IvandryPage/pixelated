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
