#include <fstream>
#include <string>

#include "certificates/LoadCertificates.h"
#include "config.h"
#include "handlers/AddTodoJsonHandler.h"
#include "handlers/DeleteTodoJsonHandler.h"
#include "handlers/EchoJsonHandler.h"
#include "handlers/GetAllTodoJsonHandler.h"
#include "handlers/JsonValidatorHandler.h"
#include "handlers/RequestHandler.h"
#include "network/ConnectionAcceptor.h"
#include "todo_storage/TodoStorage.h"

void Handle(SSLConnection&& ssl_connection, RequestHandler& request_handler) {
  auto request = ssl_connection.GetRequest();
  if (!request) {
    return;
  }
  auto response = request_handler.Handle(*request);
  ssl_connection.SendResponse(std::move(response));
  for (;;) {
    request = ssl_connection.GetRequest();
    if (!request) {
      return;
    }
    response = request_handler.Handle(*request);
    ssl_connection.SendResponse(std::move(response));
  }
}

int main() {
  std::string const cert_path = PUBLIC_KEY_PATH;
  std::string const key_path = PRIVATE_KEY_PATH;
  std::ifstream cert_file(cert_path);
  std::ifstream key_file(key_path);
  std::string const cert(std::istreambuf_iterator<char>(cert_file), {});
  std::string const key(std::istreambuf_iterator<char>(key_file), {});
  auto context = CreateContextWithCertificates(cert, key);

  auto const address = boost::asio::ip::make_address(HOST);
  auto const port = static_cast<unsigned short>(std::atoi(PORT));

  IOContext io_context{1};

  TodoStorage todo_storage;

  JsonValidatorHandler json_validator_handler;
  RequestHandler request_handler(std::move(json_validator_handler));
  request_handler.RegisterHandler("echo", std::make_unique<EchoJsonHandler>());
  request_handler.RegisterHandler(
      "atd", std::make_unique<AddTodoJsonHandler>(todo_storage));
  request_handler.RegisterHandler(
      "dtd", std::make_unique<DeleteTodoJsonHandler>(todo_storage));
  request_handler.RegisterHandler(
      "gtd", std::make_unique<GetAllTodoJsonHandler>(todo_storage));

  ConnectionAcceptor acceptor({address, port}, io_context);
  for (;;) {
    auto connection = acceptor.Accept(context);
    Handle(std::move(connection), request_handler);
  }

  return 0;
}
