set(PROTOBUF_DIR ${CMAKE_SOURCE_DIR}/proto)
set(PROTOBUF_CPP_OUT_DIR ${CMAKE_CURRENT_BINARY_DIR}/proto)

file(MAKE_DIRECTORY ${PROTOBUF_CPP_OUT_DIR})

find_program(PROTOBUF_EXECUTABLE protoc)

function(compile_proto filename)
  get_filename_component(basename ${filename} NAME_WE)
  add_custom_command(
      OUTPUT ${PROTOBUF_CPP_OUT_DIR}/${basename}.pb.cc
      DEPENDS ${filename}
      COMMAND ${PROTOBUF_EXECUTABLE}
        --cpp_out=${PROTOBUF_CPP_OUT_DIR}
        --proto_path=${PROTOBUF_DIR}
        -I=${PROTOBUF_DIR}
        ${filename}
      VERBATIM
  )
endfunction(compile_proto)

file(GLOB_RECURSE Proto_SRCS CONFIGURE_DEPENDS
  "${PROTOBUF_DIR}/*.proto"
)

foreach(proto ${Proto_SRCS})
  get_filename_component(basename ${proto} NAME_WE)
  compile_proto(${proto})
  set(PROTO_GENERATED ${PROTO_GENERATED}
    ${PROTOBUF_CPP_OUT_DIR}/${basename}.pb.cc
  )
endforeach(proto)

