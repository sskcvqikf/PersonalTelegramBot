#include "handlers/AddTodoJsonHandler.h"

AddTodoJsonHandler::AddTodoJsonHandler(TodoStorage& storage)
    : storage_(storage) {}

Json AddTodoJsonHandler::Handle(const Json& request) {
  auto message = request["message"]["text"].get<std::string>();
  auto first_entry = *request["message"]["entities"].begin();
  auto start =
      first_entry["offset"].get<int>() + first_entry["length"].get<int>() + 1;
  auto task = message.substr(start);
  storage_.AddTodo(std::move(task));

  Json response;
  response["chat_id"] = request["message"]["chat"]["id"].get<size_t>();
  response["method"] = "sendMessage";
  response["text"] = "ok";

  return response;
}
