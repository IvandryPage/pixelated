#include <iostream>

int main() {
  // std::cout print "Hellow world!" to the console;
  std::cout << "Hello World!" << std::endl;

  // Prints error
  std::cerr << "Error: " << std::endl;

  // Prints log message
  std::clog << "Log: " << std::endl;

  int age;
  std::string name;

  std::cout << "Please enter your name: " << std::endl;
  std::cin >> name;

  std::cout << "Please type your age: " << std::endl;
  std::cin >> age;

  std::cout << "Hello, " << name << "! You are " << age << " years old."
            << std::endl;

  // chaining std::cin
  std::cout << "Input name and age separated by comma: " << std::endl;
  std::cin >> name >> age;
  std::cout << "Hello, " << name << "! You are " << age << " years old."
            << std::endl;

  std::string full_name;
  std::cout << "Input your full name:" << std::endl;
  std::cin >> std::ws;  // cin.ignore() but only works for spaces
  std::getline(std::cin, full_name);
  std::cout << "Hey, " << full_name << std::endl;
  return 0;
}