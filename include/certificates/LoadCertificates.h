#ifndef PDBOT_CERTIFICATESLOADER_H_
#define PDBOT_CERTIFICATESLOADER_H_
#pragma once

#include <boost/asio/ssl/context.hpp>
#include <string_view>

using SSLContext = boost::asio::ssl::context;

SSLContext CreateContextWithCertificates(std::string_view cert,
                                         std::string_view key);

#endif  // PDBOT_CERTIFICATESLOADER_H_
