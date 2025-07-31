#pragma once

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#include <fstream>
#include <iostream>
#include <string>

struct City {
 public:
  City() = default;
  City(std::string name) {
    name_ = name;
    FindID();
  }

  std::string GetName();
  std::string GetID();

 private:
  std::string name_;
  std::string id_;
  void FindID();
};
