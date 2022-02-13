#ifndef PDBOT_BOTERROR_H_
#define PDBOT_BOTERROR_H_
#pragma once

#include <system_error>

#include "tl/expected.hpp"

enum class BotError {
  kUnsupportedCommand = 1,
  kNoCommand,
  kUserIsNotAllowed,
  kCommandFormatViolated,
};

namespace std {
template <>
struct is_error_code_enum<BotError> : public true_type {};
}  // namespace std

std::error_code make_error_code(BotError);

template <typename T>
using Result = tl::expected<T, std::error_code>;

namespace tl {
template <>
class bad_expected_access<std::error_code> : std::exception  // is this legal?
{
  explicit bad_expected_access(std::error_code code);

  const char* what() const noexcept override;

 private:
  std::string error;
};
}  // namespace tl

#endif  // PDBOT_BOTERROR_H_
