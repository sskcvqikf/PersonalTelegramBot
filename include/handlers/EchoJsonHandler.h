#ifndef PDBOT_ECHOJSONHANDLER_H_
#define PDBOT_ECHOJSONHANDLER_H_
#pragma once

#include "handlers/JsonHandler.h"

class EchoJsonHandler : public JsonHandler {
 public:
  Json Handle(const Json& request) override;
};

#endif  // PDBOT_ECHOJSONHANDLER_H_
