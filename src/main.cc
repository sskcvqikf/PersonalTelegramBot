#include <cstdlib>
#include <fstream>
#include <iostream>
#include <string>

#include "certificates/LoadCertificates.h"
#include "handlers/AddTodoJsonHandler.h"
#include "handlers/DeleteTodoJsonHandler.h"
#include "handlers/EchoJsonHandler.h"
#include "handlers/GetAllTodoJsonHandler.h"
#include "handlers/RequestHandler.h"
#include "network/ConnectionAcceptor.h"
#include "todo_storage/TodoStorage.h"

int main() {
  std::string const cert_path = std::getenv("PDBOT_PUBLIC_KEY_PATH");
  std::string const key_path = std::getenv("PDBOT_PRIVATE_KEY_PATH");
  std::ifstream cert_file(cert_path);
  std::ifstream key_file(key_path);
  std::string const cert(std::istreambuf_iterator<char>(cert_file), {});
  std::string const key(std::istreambuf_iterator<char>(key_file), {});
  auto context = CreateContextWithCertificates(cert, key);

  auto const address = boost::asio::ip::make_address(std::getenv("PDBOT_HOST"));
  auto const port =
      static_cast<unsigned short>(std::atoi(std::getenv("PDBOT_PORT")));

  IOContext io_context{1};

  TodoStorage todo_storage;

  RequestHandler request_handler;
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
    auto request = connection.GetRequest();
    auto response = request_handler.Handle(request);
    connection.SendResponse(std::move(response));
  }

  return 0;
}
