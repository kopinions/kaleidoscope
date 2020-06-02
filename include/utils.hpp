#ifndef UTILS_HPP
#define UTILS_HPP
#include <optional>
namespace utils {
const auto isalpha = [](std::optional<int> v) -> bool {
  if (v == std::nullopt) {
    return false;
  }
  return std::isalpha(*v);
};

const auto isdigit = [](std::optional<int> v) -> bool {
  if (v == std::nullopt) {
    return false;
  }
  return std::isdigit(*v);
};

const auto isspace = [](std::optional<int> v) -> bool {
  if (v == std::nullopt) {
    return false;
  }
  return std::isspace(*v);
};

const auto isalnum = [](std::optional<int> v) -> bool {
  if (v == std::nullopt) {
    return false;
  }
  return std::isalnum(*v);
};
} // namespace utils
#endif // UTILS_HPP
