#include "json_analyzer.h"

std::vector<Way> JsonAnalyzer::GetData() {
  std::vector<Way> data;

  std::ifstream fin(file_name_);
  nlohmann::json file;
  fin >> file;

  for (auto route : file["segments"]) {
    if (route["transport_types"].size() != 0 &&
        route["transport_types"].size() > transfer_limit_ + 1) {
      continue;
    }

    Way way(departure_, arrival_, date_, route["departure"], route["arrival"]);

    if (route["transport_types"].size() == 0) {
      way.AddTransport(route["from"]["transport_type"]);
    }

    for (auto transport : route["transport_types"]) {
      way.AddTransport(transport);
    }

    if (route["transport_types"].size() >= 2) {
      for (auto transfer : route["transfers"]) {
        way.AddTransfer(City(transfer["title"]));
      }
    }
    data.push_back(way);
  }

  return data;
}
