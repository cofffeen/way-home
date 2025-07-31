#pragma once

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#include <fstream>
#include <iostream>
#include <vector>

#include "city.h"

struct Way {
 public:
  Way(std::string departure, std::string arrival, std::string date,
      std::string departure_time, std::string arrival_time)
      : departure_(City(departure)),
        arrival_(City(arrival)),
        date_(date),
        departure_time_(departure_time),
        arrival_time_(arrival_time) {};

  Way(City departure_city, City arrival_city, std::string date,
      std::string departure_time, std::string arrival_time)
      : departure_(departure_city),
        arrival_(arrival_city),
        date_(date),
        departure_time_(departure_time),
        arrival_time_(arrival_time) {};

  void AddTransfer(City city);
  void AddTransport(std::string transport);

  City GetDeparture();
  City GetArrival();
  std::string GetDate();

  std::string GetDepartureTime();
  std::string GetArrivalTime();

  std::vector<City> transfers;

  std::vector<std::string> transport_types;

 private:
  City departure_;
  City arrival_;
  std::string date_;

  std::string departure_time_;
  std::string arrival_time_;
};