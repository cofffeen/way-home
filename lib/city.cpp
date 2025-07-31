#include "city.h"

std::string City::GetName() { return name_; }

std::string City::GetID() { return id_; }

void City::FindID() {
  std::string file_name = "../data/id.txt";
  int file_size = 32130;
  std::ifstream fin(file_name);

  for (int i = 0; i < file_size; ++i) {
    std::string str;
    std::getline(fin, str);

    if (str.find(name_) != std::string::npos) {
      id_ = "c" + str.substr(0, str.find(','));
      return;
    }
  }
}
