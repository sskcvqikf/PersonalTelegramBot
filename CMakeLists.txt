cmake_minimum_required(VERSION 3.18)

project(PdBot)

include(cmake/CheckCompiler.cmake)

include(cmake/CompileOptions.cmake)

include(cmake/Config.cmake)

include(cmake/Sanitizers.cmake)

include(cmake/Libraries.cmake)

include(cmake/GenerateProtobufs.cmake)

file(GLOB_RECURSE SRCS CONFIGURE_DEPENDS
    "src/certificates/*.cc"
    "src/network/*.cc"
    "src/handlers/*.cc"
    "src/todo_storage/*.cc"
    "src/errors/*.cc"
    "src/utils/*.cc"
)

add_executable(main
  src/main.cc ${SRCS} ${PROTOBUF_GENERATED}
)

target_include_directories(main PUBLIC
  include
  ${Boost_INCLUDE_DIRS}
  ${OPENSSL_INCLUDE_DIR}
  ${PROTOBUF_INCLUDE_DIR}
  ${PROTOBUF_CPP_OUT_DIR}
  ${tl_expected_INCLUDE_DIR}
)

target_link_libraries(main PUBLIC
  ${Boost_LIBRARIES}
  ${OPENSSL_LIBRARIES}
  ${PROTOBUF_LIBRARIES}
  ${tl_expected_LIBRARIES}
  Threads::Threads
  nlohmann_json::nlohmann_json
)
