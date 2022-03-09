#ifndef PDBOT_REQUESTHANDLER_H_
#define PDBOT_REQUESTHANDLER_H_
#pragma once

#include <boost/beast/http.hpp>
#include <functional>
#include <unordered_map>

#include "errors/BotError.h"
#include "handlers/JsonHandler.h"
#include "handlers/JsonValidatorHandler.h"

using StringBodyHttpRequest =
    boost::beast::http::request<boost::beast::http::string_body>;
using StringBodyHttpResponse =
    boost::beast::http::response<boost::beast::http::string_body>;

class RequestHandler final {
 public:
  using HandlersStorage =
      std::unordered_map<std::string, std::unique_ptr<JsonHandler>>;

  explicit RequestHandler(JsonValidatorHandler json_validator_handler);

  void RegisterHandler(std::string prefix,
                       std::unique_ptr<JsonHandler> handler);

  StringBodyHttpResponse Handle(const StringBodyHttpRequest& request);

 private:
  JsonValidatorHandler json_validator_handler_;
  HandlersStorage handlers_;
};

#endif  // PDBOT_REQUESTHANDLER_H_
