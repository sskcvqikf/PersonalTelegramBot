#include "network/ConnectionAcceptor.h"

#include <iostream>

ConnectionAcceptor::ConnectionAcceptor(ConnectionAcceptorCredentials creds,
                                       IOContext& io_context)
    : acceptor_(io_context,
                {std::move(creds.ip_address), std::move(creds.port)}) {}

SSLConnection ConnectionAcceptor::Accept(SSLContext& context) {
  Socket socket(acceptor_.get_executor());
  acceptor_.accept(socket);
  std::cout << socket.remote_endpoint() << std::endl;
  return SSLConnection(std::move(socket), context);
}
