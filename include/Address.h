#pragma once

#include <iostream>
#include <optional>

#include "Printable.h"

struct Address : public Printable {
  std::string city, country;
  std::optional<std::string> street, province, postal_code;
  Address() = default;
  Address(std::string city, std::string country,
          std::optional<std::string> street = std::nullopt,
          std::optional<std::string> province = std::nullopt,
          std::optional<std::string> postal_code = std::nullopt)
      : city(city),
        country(country),
        street(street),
        province(province),
        postal_code(postal_code) {}

  std::string toString() const override {
    std::string address;
    if (street && !street.value().empty()) {
      address += street.value() + ", ";
    }

    address += city + ", ";

    if (province && !province.value().empty()) {
      address += province.value() + ", ";
    }

    address += country;

    if (postal_code && !postal_code.value().empty()) {
      address += " " + postal_code.value();
    }

    return address;
  }
};