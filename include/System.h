#pragma once

#include <iostream>
#include <map>

#include "Mahasiswa.h"

class System {
 public:
  System() = default;
  System(std::map<int, Mahasiswa>& database) : database_(database) {}

  void addMahasiswa();
  void viewMahasiswa();
  void deleteMahasiswa();
  void updateMahasiswa();

 private:
  std::map<int, Mahasiswa> database_;
  void createMhs();
  void readMhs();
  void updateMhs();
  void deleteMhs();
  bool validInput();
};