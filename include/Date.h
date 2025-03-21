#pragma once
#include <iostream>

#include "Printable.h"

struct Date : public Printable {
  int value;
  Date(int year, int month, int day) {
    value = year * 10000 + month * 100 + day;
  }

  int year() const { return value / 10000; }
  int month() const { return (value / 100) % 100; }
  int day() const { return value % 100; }

  std::string toString() const override {
    auto defineMonth = [](int month) -> std::string {
      switch (month) {
        case 1:
          return "January";
        case 2:
          return "February";
        case 3:
          return "March";
        case 4:
          return "April";
        case 5:
          return "May";
        case 6:
          return "June";
        case 7:
          return "July";
        case 8:
          return "August";
        case 9:
          return "September";
        case 10:
          return "October";
        case 11:
          return "November";
        case 12:
          return "December";
      }
      return std::to_string(month);
    };

    return std::to_string(day()) + " " + defineMonth(month()) + " " +
           std::to_string(year());
  }
};