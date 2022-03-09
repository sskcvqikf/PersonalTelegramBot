#include "utils/JsonMessage.h"

std::optional<std::string> RemoveCommandFromMessage(const std::string& message,
                                                    Json entity) {
  auto const start =
      entity["offset"].get<size_t>() + entity["length"].get<size_t>() + 1;
  if (start >= message.size()) {
    return {};
  }
  return message.substr(start);
}
