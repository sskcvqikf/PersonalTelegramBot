#include "handlers/DeleteTodoJsonHandler.h"

uint32_t ParseId(const std::string& str) { return std::stoi(str); }

DeleteTodoJsonHandler::DeleteTodoJsonHandler(TodoStorage& storage)
    : storage_(storage) {}

Json DeleteTodoJsonHandler::Handle(const Json& request) {
  auto message = request["message"]["text"].get<std::string>();
  auto first_entry = *request["message"]["entities"].begin();
  auto start =
      first_entry["offset"].get<int>() + first_entry["length"].get<int>() + 1;
  auto id = ParseId(message.substr(start));
  storage_.DeleteTodo(id);

  Json response;
  response["chat_id"] = request["message"]["chat"]["id"].get<size_t>();
  response["method"] = "sendMessage";
  response["text"] = "ok";

  return response;
}
