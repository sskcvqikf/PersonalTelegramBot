#include "handlers/RequestHandler.h"

StringBodyHttpResponse CreatePayload(const StringBodyHttpRequest& request,
                                     const Json& json) {
  StringBodyHttpResponse ret(boost::beast::http::status::ok, request.version());
  ret.set(boost::beast::http::field::content_type, "application/json");
  ret.keep_alive(request.keep_alive());
  ret.body() = json.dump();
  ret.prepare_payload();
  return ret;
}

RequestHandler::RequestHandler(JsonValidatorHandler json_validator_handler)
    : json_validator_handler_(std::move(json_validator_handler)) {}

void RequestHandler::RegisterHandler(std::string prefix,
                                     std::unique_ptr<JsonHandler> handler) {
  handlers_.insert({std::move(prefix), std::move(handler)});
}

StringBodyHttpResponse RequestHandler::Handle(
    const StringBodyHttpRequest& request) {
  Json json = nlohmann::json::parse(request.body());

  auto handler = json_validator_handler_.ValidateAndGetHandler(json, handlers_);

  if (!handler) {
    return CreatePayload(request, std::move(handler).error());
  }

  auto ret = (*handler)->Handle(json);
  return CreatePayload(request, ret);
}
