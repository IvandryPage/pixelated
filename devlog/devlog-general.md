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
