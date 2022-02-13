#include "handlers/GetAllTodoJsonHandler.h"

GetAllTodoJsonHandler::GetAllTodoJsonHandler(TodoStorage& storage)
    : storage_(storage) {}

Json GetAllTodoJsonHandler::Handle(const Json& request) {
  auto todos = storage_.GetAll();

  std::string message;

  for (const auto& i : todos) {
    message += std::to_string(i.id()) + ": " + i.task() + '\n';
  }

  Json response;
  response["chat_id"] = request["message"]["chat"]["id"].get<size_t>();
  response["method"] = "sendMessage";
  response["text"] = message;

  return response;
}
