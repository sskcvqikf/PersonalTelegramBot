#include "handlers/DeleteTodoJsonHandler.h"

#include "utils/JsonMessage.h"

uint32_t ParseId(const std::string& str) { return std::stoi(str); }

DeleteTodoJsonHandler::DeleteTodoJsonHandler(TodoStorage& storage) noexcept
    : storage_(storage) {}

Json DeleteTodoJsonHandler::Handle(const Json& request) {
  auto const message = request["message"]["text"].get<std::string>();
  auto const first_entry = *request["message"]["entities"].begin();

  Json response;
  response["chat_id"] = request["message"]["chat"]["id"].get<size_t>();
  response["method"] = "sendMessage";

  auto const trimmed = RemoveCommandFromMessage(message, first_entry);
  if (!trimmed) {
    response["message"] =
        make_error_code(BotError::kCommandFormatViolated).message();
    return response;
  }

  storage_.DeleteTodo(std::stoi(*trimmed));

  response["text"] = "deleted";

  return response;
}
