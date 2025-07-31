#include "ui.h"

void UI::PrintData() {
  auto screen = ftxui::ScreenInteractive::FitComponent();

  ftxui::Elements route;

  for (int cnt = 0; first_to_print_ < data_.size() && cnt < print_limit_;
       ++first_to_print_, ++cnt) {
    auto way = data_[first_to_print_];
    std::string info = way.GetDeparture().GetName();
    info += "   " + way.transport_types[0];
    for (int i = 0; i < way.transfers.size(); ++i) {
      info += "   " + way.transfers[i].GetName();
      info += "   " + way.transport_types[i + 1];
    }
    info += "   " + way.GetArrival().GetName();

    route.push_back(
        ftxui::vbox(
            {ftxui::hbox(ftxui::text(way.GetDeparture().GetName() +
                                     "  --------  " +
                                     way.GetArrival().GetName())),
             ftxui::hbox(ftxui::text(way.GetDepartureTime() + "  --------  " +
                                     way.GetArrivalTime())),
             ftxui::hbox(ftxui::text(info)) | ftxui::border}) |
        ftxui::border);
  }

  if (data_.size() == 0) {
    route.push_back(ftxui::text("Маршрут не найден"));
  }

  auto renderer =
      ftxui::Renderer([&] { return ftxui::vbox({route}) | ftxui::border; });

  auto button_next = ftxui::Button("Next page", [&] {
    screen.ExitLoopClosure();
    screen.Exit();
    PrintData();
  });
  auto button_exit = ftxui::Button("Exit", [&] {
    screen.ExitLoopClosure();
    screen.Exit();
  });

  ftxui::Component page;

  if (first_to_print_ == data_.size()) {
    page = ftxui::Container::Vertical({
               renderer,
               ftxui::Renderer([] { return ftxui::separator(); }),
               ftxui::Container::Horizontal(
                   {ftxui::Container::Horizontal({button_exit})}),
           }) |
           ftxui::border;
  } else {
    page = ftxui::Container::Vertical({
               renderer,
               ftxui::Renderer([] { return ftxui::separator(); }),
               ftxui::Container::Horizontal(
                   {ftxui::Container::Horizontal({button_next})}),
           }) |
           ftxui::border;
  }

  screen.Loop(page);
}

void UI::GetData(City departure, City arrival, std::string date,
                 int transfer_limit) {
  requester_ = Requester(departure, arrival, date, transfer_limit);
  requester_.CommitRequest();
  json_analyser_ = JsonAnalyzer(departure, arrival, date, transfer_limit);
  data_ = json_analyser_.GetData();
}

void UI::Start() {
  auto screen = ftxui::ScreenInteractive::FitComponent();

  std::string departure;
  std::string arrival;
  std::string date;
  std::string transfer_limit;

  ftxui::Component input_departure = ftxui::Input(&departure, "departure");
  ftxui::Component input_arrival = ftxui::Input(&arrival, "arrival");
  ftxui::Component input_date = ftxui::Input(&date, "date");
  ftxui::Component input_transfer_limit =
      ftxui::Input(&transfer_limit, "transfer_limit");

  auto component = ftxui::Container::Vertical({
      input_departure,
      input_arrival,
      input_date,
      input_transfer_limit,
  });

  auto renderer = ftxui::Renderer(component, [&] {
    return ftxui::vbox({
               ftxui::hbox(ftxui::text(" Departure city : "),
                           input_departure->Render()),
               ftxui::hbox(ftxui::text(" Arrival city  : "),
                           input_arrival->Render()),
               ftxui::hbox(ftxui::text(" Date   : "), input_date->Render()),
               ftxui::hbox(ftxui::text(" Maximum transfer amount   : "),
                           input_transfer_limit->Render()),
           }) |
           ftxui::border;
  });

  auto button_exit = ftxui::Button("Exit", [&] {
    screen.ExitLoopClosure();
    screen.Exit();
  });
  auto button_find_route = ftxui::Button("Find route", [&] {
    if (transfer_limit == "") {
      transfer_limit = "0";
    }
    GetData(City(departure), City(arrival), date, std::stoi(transfer_limit));
    screen.ExitLoopClosure();
    screen.Exit();
    PrintData();
  });

  auto menu =
      ftxui::Container::Vertical({
          renderer,
          ftxui::Renderer([] { return ftxui::separator(); }),
          ftxui::Container::Horizontal(
              {ftxui::Container::Vertical({button_find_route, button_exit})}),
      }) |
      ftxui::border;

  screen.Loop(menu);
}
