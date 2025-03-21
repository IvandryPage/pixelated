#include <iostream>
#include <map>

#include "Address.h"
#include "Date.h"
#include "Mahasiswa.h"

int main() {
  std::map<int, Mahasiswa> database;
  for (int i = 0; i < 196; i++) {
    database.emplace(124240001 + i, Mahasiswa("Ivandry", Date(2004, 3, 20),
                                              Address("Kendal", "Indonesia")));
  }
  return 0;
}