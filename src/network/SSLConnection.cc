#include "network/SSLConnection.h"

#include <boost/beast/core/flat_buffer.hpp>
#include <iostream>

using FlatBuffer = boost::beast::flat_buffer;

template <bool isRequest, class Body, class Fields>
using HttpSerializer = boost::beast::http::serializer<isRequest, Body, Fields>;

constexpr auto const kServerHandshake = boost::asio::ssl::stream_base::server;

SSLConnection::SSLConnection(Socket&& socket, SSLContext& context)
    : socket_(std::move(socket)), context_(context) {}

StringBodyHttpRequest SSLConnection::GetRequest() {
  SSLStream<Socket&> stream{socket_, context_};
  stream.handshake(kServerHandshake);

  FlatBuffer buffer;
  StringBodyHttpRequest request;
  boost::beast::http::read(stream, buffer, request);

  last_stream_ = std::move(stream);
  return request;
}

void SSLConnection::SendResponse(StringBodyHttpResponse response) {
  HttpSerializer<StringBodyHttpResponse::is_request::value,
                 StringBodyHttpResponse::body_type,
                 StringBodyHttpResponse::fields_type>
      serializer(response);

  boost::beast::http::write(last_stream_.value(), serializer);
}
