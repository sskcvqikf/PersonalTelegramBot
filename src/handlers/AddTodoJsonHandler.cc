#include "handlers/AddTodoJsonHandler.h"

#include "utils/JsonMessage.h"

AddTodoJsonHandler::AddTodoJsonHandler(TodoStorage& storage) noexcept
    : storage_(storage) {}

Json AddTodoJsonHandler::Handle(const Json& request) {
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

  storage_.AddTodo(std::move(*trimmed));

  response["text"] = "added";

  return response;
}
