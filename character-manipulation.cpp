// Character Manipulation

#include <cstring>
#include <iostream>

int main() {
  std::cout << "C is alphanumeric: " << std::isalnum('C') << std::endl;
  std::cout << "^ is alphabetic: " << std::isalpha('^') << std::endl;
  std::cout << "_ space is a blank: " << std::isblank(' ') << std::endl;
  std::cout << "std::islower and std::isupper"
            << std::endl;  // could be use to count how many uppercase and how
                           // many lowercase

  char input_char('a');
  if (std::isalnum(input_char))
    std::cout << input_char << " is alphanumeric!" << std::endl;

  std::cout << "1 is a digit: " << std::isdigit('1') << std::endl;

  // turning string to lowercase or uppercase

  char original_str[]{"Home sweet home, Baby"};
  std::cout << original_str << std::endl;
  char destination_str[std::size(original_str)];

  for (size_t i{}; i < std::size(original_str); i++)
    destination_str[i] = std::toupper(original_str[i]);

  std::cout << "Original string : " << original_str << std::endl;
  std::cout << "Uppercase string : " << destination_str << std::endl;

  char input[] = "/home/user/hello.cpp";
  char *output = std::strrchr(input, '/');
  if (output) std::cout << output + 1 << std::endl;
  return 0;
}