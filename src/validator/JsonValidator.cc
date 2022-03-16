#include "validator/JsonValidator.h"

#include "config.h"
#include "errors/BotError.h"

int64_t GetChatId(const Json& json) {
  if (json.contains("message")) {
    return json["message"]["chat"]["id"].get<int64_t>();
  }
  if (json.contains("edited_message")) {
    return json["edited_message"]["chat"]["id"].get<int64_t>();
  }
  if (json.contains("channel_post")) {
    return json["channel_post"]["chat"]["id"].get<int64_t>();
  }
  if (json.contains("edited_channel_post")) {
    return json["edited_channel_post"]["chat"]["id"].get<int64_t>();
  }
  std::terminate();  // TODO: Handle panic here
}

Result<void> ValidateMessage(const Json& json) {
  if (!json.contains("message") or !json["message"].contains("entities")) {
    return tl::make_unexpected(make_error_code(BotError::kNoCommand));
  }
  auto message = json["message"];
  if (!message.contains("text")) {
    return tl::make_unexpected(make_error_code(BotError::kNoCommand));
  }
  return {};
}

ResultRef<JsonHandler> GetJsonHandler(
    const Json& json, const JsonValidator::HandlersStorage& handlers) {
  auto const message = json["message"]["text"].get<std::string>();
  auto const entities = json["message"]["entities"];
  if (entities.empty()) {
    return tl::make_unexpected(
        make_error_code(BotError::kCommandFormatViolated));
  }

  auto first_entity = *entities.begin();
  if (first_entity["type"] != "bot_command") {
    return tl::make_unexpected(
        make_error_code(BotError::kCommandFormatViolated));
  }

  auto prefix = message.substr(
      first_entity["offset"].get<int>() + 1,  // ignore / at the begin of prefix
      first_entity["length"].get<int>() - 1);
  if (auto found = handlers.find(prefix); found != handlers.end()) {
    return *found->second;
  }
  return tl::make_unexpected(make_error_code(BotError::kNoCommand));
}

Json CreateSendMessageBody(int64_t chat_id, std::string message) {
  Json ret;
  ret["chat_id"] = chat_id;
  ret["method"] = "sendMessage";
  ret["text"] = message;
  return ret;
}

tl::expected<JsonHandler*, Json> JsonValidator::ValidateAndGetHandler(
    const Json& json, const HandlersStorage& handlers) {
  auto chat_id = GetChatId(json);

  if (chat_id != USER_ID) {
    return tl::make_unexpected(CreateSendMessageBody(
        chat_id, make_error_code(BotError::kUserIsNotAllowed).message()));
  }

  auto validation_result = ValidateMessage(json);
  if (!validation_result) {
    return tl::make_unexpected(
        CreateSendMessageBody(chat_id, validation_result.error().message()));
  }

  auto handler = GetJsonHandler(json, handlers);
  if (!handler) {
    return tl::make_unexpected(
        CreateSendMessageBody(chat_id, handler.error().message()));
  }

  return &(handler->get());
}
