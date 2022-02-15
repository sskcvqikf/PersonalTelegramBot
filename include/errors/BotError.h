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

#endif  // PDBOT_BOTERROR_H_
