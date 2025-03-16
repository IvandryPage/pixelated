#include <cstring>
#include <iostream>

int main() {
  // Traffic Lights
  std::cout << "Current light status (r/g/y) : ";
  char status;
  std::cin >> status;
  std::tolower(status);

  std::cout << "Should Go? : ";
  bool go = std::strcmp(&status, "g") == 0;
  if (go) {
    std::cout << std::boolalpha << go << "\nYou are free to pull the gas.\n";
  } else {
    if (std::strcmp(&status, "y") == 0) {
      std::cout << std::boolalpha << go
                << "\nGet ready! Buckle up your stuff!\n";
    } else {
      std::cout << std::boolalpha << go << "\nYou must stop and wait!";
    }
  }
}