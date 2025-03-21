#pragma once

#include <iostream>

#include "Address.h"
#include "Date.h"

class Mahasiswa {
 public:
  Mahasiswa() = default;
  Mahasiswa(std::string nama, Date birthday, Address address);

  const std::string& name() const;
  const Date& birthday() const;
  const Address& address() const;

  void setAddress(Address& address);

 private:
  std::string name_;
  Date birthday_;
  Address address_;
};