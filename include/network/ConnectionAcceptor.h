#ifndef PDBOT_CONNECTIONACCEPTOR_H_
#define PDBOT_CONNECTIONACCEPTOR_H_
#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/context.hpp>
#include <string>

#include "network/SSLConnection.h"

using IPAddress = boost::asio::ip::address;
using Port = unsigned short;
using IOContext = boost::asio::io_context;
using TCP = boost::asio::ip::tcp;

struct ConnectionAcceptorCredentials final {
  IPAddress const ip_address;
  Port const port;
};

class ConnectionAcceptor final {
 public:
  ConnectionAcceptor(ConnectionAcceptorCredentials creds,
                     IOContext& io_context);

  SSLConnection Accept(SSLContext& context);

 private:
  TCP::acceptor acceptor_;
};

#endif  // PDBOT_CONNECTIONACCEPTOR_H_
