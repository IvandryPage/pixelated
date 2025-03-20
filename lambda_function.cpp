// LambdaFunction

#include <iostream>

int main() {
  // Lambda function signature
  // [capture list] (parameters) return_type(optional) { }

  auto func = []() { std::cout << "Hello World!" << std::endl; };

  func();

  []() { std::cout << "Calling lambda function directly" << std::endl; }();

  int max = [](int a, int b) { return (a > b) ? a : b; }(7, 18);

  std::cout << "Max from lambda: " << max << std::endl;
  std::cout << "Sum : " << [](int a, int b) { return a + b; }(7, 18)
            << std::endl;

  auto explicitReturn = [](double a, double b) -> int { return a + b; };
  std::cout << "The sum from explicitReturn: " << explicitReturn(1.5, 3.5)
            << std::endl;

  std::cout << "Message: " << []() { return (true) ? "bla" : "blabla"; }()
            << std::endl;

  // Caputer List
  int c{42};
  auto function = [c]() { std::cout << "  Inner value : " << c << std::endl; };

  for (size_t i{}; i < 5; ++i) {
    std::cout << "Outer value : " << c << std::endl;
    function();
    ++c;
  }

  // Capture by reference
  int d{43};
  auto funk = [&d]() {
    std::cout << "Inner value : " << d << ". &inner : " << &d << std::endl;
  };

  for (size_t i{0}; i < 5; i++) {
    std::cout << "Outer value : " << c << ". &outer : " << &c << std::endl;
    funk();
    ++d;
  }

  // capture all
  // = by value
  auto funk2 = [=]() {
    std::cout << "Inner value c: " << c << ". &address: " << &c << std::endl;
    std::cout << "Inner value d: " << d << ". &address: " << &d << std::endl;
  };

  // & by reference
  auto funk3 = [&]() {
    std::cout << "Inner value c: " << c << ". &address: " << &c << std::endl;
    std::cout << "Inner value d: " << d << ". &address: " << &d << std::endl;
  };

  funk2();
  funk3();
  std::cout << "DONE Bang!" << std::endl;
  return 0;
}