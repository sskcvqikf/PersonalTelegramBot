set(Boost_USE_STATIC_LIBS ON)
find_package(Boost COMPONENTS system REQUIRED)

find_package(OpenSSL REQUIRED)

find_package(Threads REQUIRED)

find_package(nlohmann_json REQUIRED)

find_package(Protobuf REQUIRED)
