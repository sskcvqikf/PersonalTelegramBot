#include "handlers/EchoJsonHandler.h"

Json EchoJsonHandler::Handle(const Json& request) {
  Json response;
  response["chat_id"] = request["message"]["chat"]["id"].get<size_t>();
  response["method"] = "sendMessage";
  response["text"] = request["message"]["text"].get<std::string>();
  return response;
}
