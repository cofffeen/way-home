#pragma once

#ifdef max
#undef max
#endif

#ifdef min
#undef min
#endif

#include <fstream>
#include <iostream>
#include <memory>
#include <string>
#include <vector>

#include "requester.h"
#include "ftxui/component/captured_mouse.hpp"
#include "ftxui/component/component.hpp"
#include "ftxui/component/component_base.hpp"
#include "ftxui/component/component_options.hpp"
#include "ftxui/component/screen_interactive.hpp"
#include "ftxui/dom/elements.hpp"
#include "ftxui/screen/color.hpp"
#include "ftxui/util/ref.hpp"

class UI {
 public:
  UI() = default;
  UI(UI& other) { this->data_ = other.data_; }
  ~UI() = default;
  UI& operator=(UI& other) {
    this->data_ = other.data_;
    return *this;
  }

  void Start();
  void GetData(City departure, City arrival, std::string date,
               int transfer_limit);
  void PrintData();

 private:
  std::vector<Way> data_;
  int print_limit_ = 5;
  int first_to_print_ = 0;
  Requester requester_;
  JsonAnalyzer json_analyser_;
};
