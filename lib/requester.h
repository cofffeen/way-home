#pragma once

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#include <cpr/cpr.h>

#include <chrono>
#include <ctime>
#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>

#include "json_analyzer.h"

class Requester {
 public:
  Requester() = default;
  Requester(City departure, City arrival, std::string date,
            int transfer_limit) {
    departure_ = departure;
    arrival_ = arrival;
    date_ = date;
    transfer_limit_ = transfer_limit;
    file_name_ = "../cache/" + date_ + "-" + departure_.GetID() + "-" +
                 arrival_.GetID() + ".json";
  }
  Requester(Requester& other) {
    this->departure_ = other.departure_;
    this->arrival_ = other.arrival_;
    this->date_ = other.date_;
    this->transfer_limit_ = other.transfer_limit_;
    this->file_name_ = other.file_name_;
  }
  ~Requester() = default;

  Requester& operator=(Requester other) {
    this->departure_ = other.departure_;
    this->arrival_ = other.arrival_;
    this->date_ = other.date_;
    this->transfer_limit_ = other.transfer_limit_;
    this->file_name_ = other.file_name_;

    return *this;
  }

  void CommitRequest();

 private:
  City departure_;
  City arrival_;
  std::string date_;
  std::string file_name_;
  int transfer_limit_;

  long long GetTime();
};
