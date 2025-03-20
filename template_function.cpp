// Template function for repetitive function
#include <concepts>
#include <cstring>
#include <iostream>
// the bad way
/*
int maximum (int a, int b)
{
    return (a > b) ? a : b;
}

std::string maximum (const std::string &a, const std::string &b)
{
    return (a > b) ? a : b;
}

long long int maximum(long long int a, long long int b)
{
    return (a > b) ? a : b;
}

*/

// the best way - it expect the same data type
template <typename T>
T maximum(T a, T b) {
  return (a > b) ? a : b;
}

template <typename T>
T multiply(T a, T b) {
  std::cout << "In - &a: " << &a << std::endl;
  return a * b;
}

// template by references
template <typename T>
const T sum(const T &a, const T &b) {
  std::cout << "In - &a: " << &a << std::endl;
  return a + b;
}

// TEMPLATE SPECIALIZATION
template <>
const char *maximum<const char *>(const char *a, const char *b);

template <>
int maximum<int>(int a, int b);

// C++ CONCEPTS
/*
    same_as
    derived_from
    convertible_to
    common_reference_with
    common_with
    integral
    signed_integral
    unsigned_integral
    floating_point
 */

template <typename T>
  requires std::integral<T>
T add(T a, T b) {
  return a + b;
}

int main() {
  float x{8.5f};
  float y{5.5f};
  auto result = maximum(x, y);
  std::cout << "result1 : " << result << std::endl;

  std::string z{"Hello"};
  std::string a{"World"};
  auto result2 = maximum(z, a);
  std::cout << "result2 : " << result2 << std::endl;

  int b{7};
  int c{3};
  auto result3 = multiply(b, c);
  std::cout << "result3 : " << result3 << std::endl;

  // problematic because string doesn't support multiplication
  // auto result4 = multiply(z, a);

  // it compares the address not the value. So, it would output the value of the
  // maximum address
  float *p_y{&y};
  float *p_x{&x};
  auto result4 = maximum(p_x, p_y);
  std::cout << "result4 : " << *result4 << std::endl;

  // TEMPLATE TYPE DEDUCTION
  maximum<double>(b, c);  // it would return in double even b and c are integer

  // passing by reference
  std::cout << std::endl;
  std::cout << "Out - &a: " << &y << std::endl;
  sum(y, x);
  std::cout << "Out - &a: " << &y << std::endl;

  // CONCEPTS C++
  char a_0{10};
  char a_1{20};
  auto result_a = add(a_0, a_1);
  return 0;
}

template <>
const char *maximum<const char *>(const char *a, const char *b) {
  return (std::strcmp(a, b) > 0) ? a : b;
}