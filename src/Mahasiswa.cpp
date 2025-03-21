#include "Mahasiswa.h"

Mahasiswa::Mahasiswa(std::string name, Date birthday, Address address)
    : name_(name), birthday_(birthday), address_(address) {}

const std::string& Mahasiswa::name() const { return name_; }
const Date& Mahasiswa::birthday() const { return birthday_; }
const Address& Mahasiswa::address() const { return address_; }
void Mahasiswa::setAddress(Address& address) { address_ = address; }