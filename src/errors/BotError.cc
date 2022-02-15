#include "errors/BotError.h"

#include <cassert>

struct BotErrorCategory : public std::error_category {
  const char* name() const noexcept override;
  std::string message(int ev) const override;
};

const char* BotErrorCategory::name() const noexcept { return "flights"; }

std::string BotErrorCategory::message(int ev) const {
  switch (static_cast<BotError>(ev)) {
    case BotError::kCommandFormatViolated:
      return "Format for given format is violated";
    case BotError::kNoCommand:
      return "No command supplyed";
    case BotError::kUnsupportedCommand:
      return "Given command isn't supported";
    case BotError::kUserIsNotAllowed:
      return "Uebivay";
    default:
      assert(false);
  }
}

const BotErrorCategory& GetBotErrorCategory() {
  static BotErrorCategory bot_error_category;
  return bot_error_category;
}

std::error_code make_error_code(BotError e) {
  return {static_cast<int>(e), GetBotErrorCategory()};
}
