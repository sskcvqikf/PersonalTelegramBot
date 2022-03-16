#include "network/SSLConnection.h"

#include <boost/beast/core/flat_buffer.hpp>

using FlatBuffer = boost::beast::flat_buffer;

template <bool isRequest, class Body, class Fields>
using HttpSerializer = boost::beast::http::serializer<isRequest, Body, Fields>;

constexpr auto const kServerHandshake = boost::asio::ssl::stream_base::server;

SSLConnection::SSLConnection(Socket&& socket, SSLContext& context)
    : socket_(std::move(socket)),
      context_(context),
      stream_(socket_, context_) {
  stream_.handshake(kServerHandshake);
}

std::optional<StringBodyHttpRequest> SSLConnection::GetRequest() {
  FlatBuffer buffer;
  StringBodyHttpRequest request;
  boost::beast::error_code ec;
  boost::beast::http::read(stream_, buffer, request, ec);

  if (request.need_eof() or ec == boost::beast::http::error::end_of_stream) {
    stream_.shutdown(ec);
    return {};
  }
  return request;
}

void SSLConnection::SendResponse(StringBodyHttpResponse response) {
  HttpSerializer<StringBodyHttpResponse::is_request::value,
                 StringBodyHttpResponse::body_type,
                 StringBodyHttpResponse::fields_type>
      serializer(response);

  boost::beast::http::write(stream_, serializer);
}
