add_library(way_home STATIC city.cpp city.h way.cpp way.h json_analyzer.cpp json_analyzer.h requester.cpp requester.h  ui.cpp ui.h)

target_link_libraries(way_home
PUBLIC ftxui::screen
PUBLIC ftxui::component
PUBLIC ftxui::dom)

target_link_libraries(way_home PUBLIC cpr::cpr)
target_link_libraries(way_home PUBLIC nlohmann_json::nlohmann_json)