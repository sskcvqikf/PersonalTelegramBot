#ifndef PDBOT_REQUESTHANDLER_H_
#define PDBOT_REQUESTHANDLER_H_
#pragma once

#include <boost/beast/http.hpp>
#include <unordered_map>

#include "handlers/JsonHandler.h"

using StringBodyHttpRequest =
    boost::beast::http::request<boost::beast::http::string_body>;
using StringBodyHttpResponse =
    boost::beast::http::response<boost::beast::http::string_body>;

class RequestHandler final {
 public:
  void RegisterHandler(std::string prefix,
                       std::unique_ptr<JsonHandler> handler);

  StringBodyHttpResponse Handle(const StringBodyHttpRequest& request);

 private:
  std::unordered_map<std::string, std::unique_ptr<JsonHandler>> handlers_;
};

#endif  // PDBOT_REQUESTHANDLER_H_
