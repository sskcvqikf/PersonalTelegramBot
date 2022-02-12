#ifndef PDBOT_JSONHANDLER_H_
#define PDBOT_JSONHANDLER_H_
#pragma once

#include <nlohmann/json.hpp>

using Json = nlohmann::json;

class JsonHandler {
 public:
  virtual Json Handle(const Json& request) = 0;
  virtual ~JsonHandler() {}
};

#endif  // PDBOT_JSONHANDLER_H_
