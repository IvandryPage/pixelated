#include <iostream>

int addNumber(int m, int n) { return m + n; }

int main() {
  int number;  // because number isn't assign to a value, it has garbage value
               // (random value in memory)
  float decimal = 10.0f;  // if without f symbol, C++ treated it as a double

  // parantheses initialization doesnt't make compiler error like curly bracket
  // initialization
  int sec_num(50);
  double precise_decimal{15.000004};  // curlybracket initialization prevents
                                      // narrowing / loosing precisions

  int sum2number = addNumber(sec_num, number);
  std::cout << "Sum of sec_num and number: " << sum2number << std::endl;
  return 0;
}