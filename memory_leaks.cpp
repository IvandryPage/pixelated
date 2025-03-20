// Memory leaks

#include <iostream>

int main() {
  // reassingment dynamic allocation to stack variable
  int *p_address1{new int{69}};  // lives in address1

  int address2{98};  // lives in address2

  p_address1 = &address2;  // this will cause a memory leaks.
                           // because p_address1 is still in the memory but we
                           // points the p_address1 to address2 we lost the
                           // access of the address 1; memory has been leaked.

  // double allocation
  int *p_address3{new int{155}};

  // should delete the p_address3 before assign

  p_address3 =
      new int{123};  // we lost access to int{155}. memory with int{155} leaked.

  // pointer in local scope

  {
    int *p_number2{new int{57}};
  }
  // memory with int{57} leaked.
  return 0;
}