#include "System.h"

void System::addMahasiswa() {
  int key;
  std::string name;
  std::tuple<short, short, short int> date{};
  std::tuple<std::string, std::string, std::string, std::string, std::string>
      address{};

  std::cout << "------ Add Mahasiswa ------\n";
  do {
    std::cout << "NIM\t: ";
    std::cin >> key;
  } while (!validInput());

  std::cout << "Name\t: ";
  std::cin.ignore(10000, '\n');
  getline(std::cin, name);

  char c;
  std::cout << "(YYYY/MM/DD)\n";
  std::cout << "Tanggal Lahir\t: ";
  std::cin >> std::get<0>(date) >> c >> std::get<1>(date) >> c >>
      std::get<2>(date);

  std::cout << "City\t: ";
  std::cin >> std::get<0>(address);
  std::cout << "Country\t: ";
  std::cin >> std::get<1>(address);
  std::cout << "Street\t: ";
  std::cin >> std::get<2>(address);
  std::cout << "Province\t: ";
  std::cin >> std::get<3>(address);
  std::cout << "Postal Code\t: ";
  std::cin >> std::get<4>(address);

  database_.emplace(
      key,
      Mahasiswa(name,
                Date(std::get<0>(date), std::get<1>(date), std::get<2>(date)),
                Address(std::get<0>(address), std::get<1>(address),
                        std::get<2>(address), std::get<3>(address),
                        std::get<4>(address))));
}
void System::viewMahasiswa() {
  std::cout << "------ View Mahasiswa ------\n";
  for (auto& m : database_) {
    std::cout << m.first << " " << m.second.name() << " "
              << m.second.birthday().toString() << " "
              << m.second.address().toString() << std::endl;
  }
  std::cin.ignore();
  std::cin.get();
}
void System::deleteMahasiswa() {
  std::cout << "------ Delete Mahasiswa ------\n";
  std::cout << "NIM\t: ";
  int key;
  std::cin >> key;

  database_.erase(key);
}

bool System::validInput() {
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(10000, '\n');
    std::cout << "Input not valid!";
    return false;
  }
  return true;
}