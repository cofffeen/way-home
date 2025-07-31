#include "requester.h"

long long Requester::GetTime() {
  auto now = std::chrono::system_clock::now();
  auto time_in_seconds =
      std::chrono::time_point_cast<std::chrono::seconds>(now);
  auto value = time_in_seconds.time_since_epoch().count();
  return value;
}

void Requester::CommitRequest() {
  std::ifstream fin(file_name_);

  long long now_seconds = GetTime();

  if (fin.good()) {
    nlohmann::json data;
    fin >> data;
    if (now_seconds - data["request_time"].get<long long>() <= 5 * 60 * 60) {
      return;
    }
  }

  cpr::Parameters parameters =
      cpr::Parameters{{"apikey", "ключ"},
                      {"from", departure_.GetID()},
                      {"to", arrival_.GetID()},
                      {"format", "json"},
                      {"date", date_},
                      {"transfers", "true"}};
  cpr::Response response = cpr::Get(
      cpr::Url{"https://api.rasp.yandex.net/v3.0/search/"}, parameters);

  std::ofstream fout(file_name_);

  nlohmann::json data = nlohmann::json::parse(response.text);
  data["request_time"] = now_seconds;

  if (fout.is_open()) {
    fout << data.dump();

    fout.close();
  }
}
