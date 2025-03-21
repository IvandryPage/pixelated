#include <iostream>
#include <map>

#include "Address.h"
#include "Date.h"
#include "Mahasiswa.h"
#include "System.h"

enum MenuEnum { ADD = 1, VIEW, DELETE, EXIT };

void clear() {
#ifdef __WIN32__
  system("cls");
#else
  system("clear");
#endif
}

int main() {
  std::map<int, Mahasiswa> database;
  System system(database);

  while (true) {
    clear();
    std::cout << "-------- Student Management --------\n";
    std::cout << "1. Add new mahasiswa\n";
    std::cout << "2. View Student Details\n";
    std::cout << "3. Delete Student\n";
    std::cout << "4. Exit\n";
    std::cout << "------------------------------------\n";
    std::cout << "> Type your choice : ";

    short input = 0;
    std::cin >> input;
    if (std::cin.fail()) {
      std::cin.clear();
      std::cin.ignore(1000, '\n');
      std::cout << "Non Number Input!\n";
      continue;
    }

    switch (input) {
      case ADD:
        system.addMahasiswa();
        break;
      case VIEW:
        system.viewMahasiswa();
        break;
      case DELETE:
        system.deleteMahasiswa();
        break;
      case EXIT:
        std::cout << "Thanks for playing\n";
        exit(0);
        break;
      default:
        std::cout << "Doesn't exist!\n";
    }
  }
  return 0;
}