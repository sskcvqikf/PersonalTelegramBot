#include "errors/BotError.h"

#include <cassert>
#include <iostream>

struct BotErrorCategory : public std::error_category {
  const char* name() const noexcept override;
  std::string message(int ev) const override;
};

const char* BotErrorCategory::name() const noexcept { return "bot"; }

std::string BotErrorCategory::message(int ev) const {
  switch (static_cast<BotError>(ev)) {
    case BotError::kCommandFormatViolated:
      return "Format for given command is violated";
    case BotError::kNoCommand:
      return "No command supplied";
    case BotError::kUnsupportedCommand:
      return "Given command isn't supported";
    case BotError::kUserIsNotAllowed:
      return "Access denied";
    default:
      assert(false);
  }
}

namespace {
BotErrorCategory bot_error_category{};
}

const BotErrorCategory& GetBotErrorCategory() { return bot_error_category; }

std::error_code make_error_code(BotError e) {
  return {static_cast<int>(e), bot_error_category};
}
