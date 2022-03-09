#ifndef PDBOT_SSLCONNECTION_H_
#define PDBOT_SSLCONNECTION_H_
#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ssl/context.hpp>
#include <boost/asio/ssl/stream.hpp>
#include <boost/beast/http.hpp>
#include <boost/beast/ssl.hpp>
#include <optional>

using Socket = boost::asio::ip::tcp::socket;
using SSLContext = boost::asio::ssl::context;
using StringBodyHttpRequest =
    boost::beast::http::request<boost::beast::http::string_body>;
using StringBodyHttpResponse =
    boost::beast::http::response<boost::beast::http::string_body>;

template <typename Socket>
using SSLStream = boost::beast::ssl_stream<Socket>;

class SSLConnection final {
 public:
  explicit SSLConnection(Socket&& socket, SSLContext& context);

  std::optional<StringBodyHttpRequest> GetRequest();

  void SendResponse(StringBodyHttpResponse response);

 private:
  Socket socket_;
  SSLContext& context_;
  SSLStream<Socket&> stream_;
};

#endif  // PDBOT_SSLCONNECTION_H_
