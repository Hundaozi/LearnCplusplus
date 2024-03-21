#pragma once
#include <any>
#include <stdexcept>
#include <string>

namespace hundaozi {
namespace json {
inline std::any Error(const std::string &message) {
  throw std::logic_error(message);
}
} // namespace json
} // namespace hundaozi