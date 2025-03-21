#pragma once
#include <iostream>

class Printable {
 public:
  virtual std::string toString() const = 0;
  virtual void print() const { std::cout << toString() << '\n'; }

  virtual ~Printable() = default;
};