#include "handlers/RequestHandler.h"

void RequestHandler::RegisterHandler(std::string prefix,
                                     std::unique_ptr<JsonHandler> handler) {
  handlers_.insert({std::move(prefix), std::move(handler)});
}

StringBodyHttpResponse RequestHandler::Handle(
    const StringBodyHttpRequest& request) {
  Json json = nlohmann::json::parse(request.body());
  auto message = json["message"]["text"].get<std::string>();
  auto entry = *json["message"]["entities"].begin();
  if (entry["type"] == "bot_command") {
    auto prefix = message.substr(entry["offset"].get<int>() + 1,
                                 entry["length"].get<int>() - 1);
    if (auto found = handlers_.find(prefix); found != handlers_.end()) {
      auto response_json = found->second->Handle(json);
      StringBodyHttpResponse response{boost::beast::http::status::ok,
                                      request.version()};
      response.set(boost::beast::http::field::content_type, "application/json");
      response.keep_alive(request.keep_alive());
      response.body() = response_json.dump();
      response.prepare_payload();
      return response;
    }
  }
  throw std::runtime_error("No such hanler");
}
