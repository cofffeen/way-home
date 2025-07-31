#include "way.h"

City Way::GetDeparture() { return departure_; }
City Way::GetArrival() { return arrival_; }
std::string Way::GetDate() { return date_; }

std::string Way::GetDepartureTime() { return departure_time_; }
std::string Way::GetArrivalTime() { return arrival_time_; }

void Way::AddTransfer(City city) { transfers.push_back(city); }

void Way::AddTransport(std::string transport) {
  transport_types.push_back(transport);
}
