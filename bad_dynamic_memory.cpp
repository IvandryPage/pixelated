#include <iostream>

int main() {
  int *p_number1{new int{67}};
  std::cout << "*p_number1 before delete: " << *p_number1 << std::endl;
  delete p_number1;
  std::cerr
      << "WARNING : p_number1 doesn't set to null pointer. Unexpected Value!"
      << std::endl;
  std::cout << "*p_number1 before after: " << *p_number1 << std::endl;

  // if new fails
  // could be using std::nothrow or try catch

  for (int i{}; i < 10000000; ++i) {
    try {
      int *data = new int[1000000000];
    } catch (std::exception &ex) {
      std::cerr << "ERROR: " << ex.what() << std::endl;
      break;
    }
  }

  for (size_t i{0}; i < 100; i++) {
    int *data = new (std::nothrow) int[1000000000];

    if (data != nullptr) {
      std::cout << "Data allocated" << std::endl;
    } else {
      std::cout << "Data allocation failed" << std::endl;
    }
  }
  std::cout << "Program ending well!" << std::endl;
  return 0;
}