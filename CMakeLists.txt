cmake_minimum_required(VERSION 3.18)

project(PdBot)

include(cmake/CheckCompiler.cmake)

include(cmake/CompileOptions.cmake)

include(cmake/Config.cmake)

include(cmake/Libraries.cmake)

include(cmake/Sanitizers.cmake)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS
    "src/certificates/*.cc"
    "src/network/*.cc"
    "src/handlers/*.cc"
)

add_executable(main src/main.cc ${SRCS})

target_include_directories(main PUBLIC
  include
  ${Boost_INCLUDE_DIRS}
  ${OPENSSL_INCLUDE_DIR}
)

target_link_libraries(main PUBLIC
  ${Boost_LIBRARIES}
  ${OPENSSL_LIBRARIES}
  Threads::Threads
  nlohmann_json::nlohmann_json
)
