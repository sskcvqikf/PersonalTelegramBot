#ifndef PDBOT_JSONMESSAGE_H_
#define PDBOT_JSONMESSAGE_H_
#pragma once

#include <nlohmann/json.hpp>
#include <optional>

using Json = nlohmann::json;

std::optional<std::string> RemoveCommandFromMessage(const std::string& message,
                                                    Json entity);

#endif  // PDBOT_JSONMESSAGE_H_
