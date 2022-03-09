#ifndef PDBOT_JSONVALIDATORHANDLER_H_
#define PDBOT_JSONVALIDATORHANDLER_H_
#pragma once

#include <nlohmann/json.hpp>
#include <tl/expected.hpp>

#include "handlers/JsonHandler.h"

using Json = nlohmann::json;

class JsonValidatorHandler {
 public:
  using HandlersStorage =
      std::unordered_map<std::string, std::unique_ptr<JsonHandler>>;

  tl::expected<JsonHandler*, Json> ValidateAndGetHandler(
      const Json& json, const HandlersStorage& handlers);
};

#endif  // PDBOT_JSONVALIDATORHANDLER_H_
