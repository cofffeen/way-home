#pragma once

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

#include "way.h"

class JsonAnalyzer {
 public:
  JsonAnalyzer() = default;
  JsonAnalyzer(City& departure, City& arrival, std::string date,
               int transfer_limit) {
    departure_ = departure;
    arrival_ = arrival;
    date_ = date;
    transfer_limit_ = transfer_limit;
    file_name_ = "../cache/" + date_ + "-" + departure_.GetID() + "-" +
                 arrival_.GetID() + ".json";
  }
  JsonAnalyzer(JsonAnalyzer& other) {
    this->departure_ = other.departure_;
    this->arrival_ = other.arrival_;
    this->date_ = other.date_;
    this->transfer_limit_ = other.transfer_limit_;
    this->file_name_ = other.file_name_;
  }
  ~JsonAnalyzer() = default;

  JsonAnalyzer& operator=(JsonAnalyzer other) {
    this->departure_ = other.departure_;
    this->arrival_ = other.arrival_;
    this->date_ = other.date_;
    this->transfer_limit_ = other.transfer_limit_;
    this->file_name_ = other.file_name_;

    return *this;
  }

  std::vector<Way> GetData();

 private:
  City departure_;
  City arrival_;
  std::string date_;
  std::string file_name_;
  int transfer_limit_;
};
