#include "certificates/LoadCertificates.h"

boost::asio::ssl::context CreateContextWithCertificates(std::string_view cert,
                                                        std::string_view key) {
  boost::asio::ssl::context context(boost::asio::ssl::context::tlsv12);
  context.use_certificate_chain(boost::asio::buffer(cert.data(), cert.size()));

  context.use_private_key(boost::asio::buffer(key.data(), key.size()),
                          boost::asio::ssl::context::file_format::pem);

  return context;
}
