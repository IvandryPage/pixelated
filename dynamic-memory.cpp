// Dynamic Memory Allocation
#include <iostream>

// Stack and Heap
// Heap has control of when memory is allocated and when it's released
// controlled through new and delete

int main() {
  int *p_int{nullptr};
  p_int = new int;  // dynamically allocate space for a single int on the heap

  *p_int = 77;
  std::cout << std::endl;
  std::cout << "Dynamically allocating memory : " << std::endl;
  std::cout << "p_int : " << *p_int << std::endl;

  {
    int local_var{33};             // dies when out of scope
    int *local_ptr_var = new int;  // memory still be on the heap but can't be
                                   // accesed from everywhere cause the pointer
                                   // into that address is died
  }

  delete p_int;     // delete memory
  p_int = nullptr;  // always reset to nullptr

  // declaration

  int *p_num{new int};       // memory allocation contains junk value
  int *p_num1{new int(22)};  // use direct initialization
  int *p_num2{new int{23}};  // use uniform initialization

  std::cout << p_num << std::endl;
  std::cout << *p_num << std::endl;

  std::cout << p_num1 << std::endl;
  std::cout << *p_num1 << std::endl;

  std::cout << p_num2 << std::endl;
  std::cout << *p_num2 << std::endl;
  // relesea memory
  delete p_num;
  p_num = nullptr;
  delete p_num1;
  p_num1 = nullptr;
  delete p_num2;
  p_num2 = nullptr;

  // BAD IMPLEMENTATION OF POINTER
  int *p_number;   // contains junk address : could be anything
  *p_number = 55;  // Writing into unknown junk address : could be something
                   // important like OS
  // it would cause the program to crash

  // initializing pointer to null
  int *p_number2{};  // initialized with pointer of zero : nullptr

  *p_number = 33;  // Writing into a pointer pointing nowhere : BAD, CRASH
  std::cout << std::endl;
  std::cout << "Reading and writing through nullptr: " << *p_number
            << std::endl;

  return 0;
}