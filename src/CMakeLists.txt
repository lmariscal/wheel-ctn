file(GLOB WHEEL_CTN_SOURCES
  main.cc
  utils.cc
  ctn.cc
)

add_executable(wheel_ctn ${WHEEL_CTN_SOURCES})

set_target_properties(wheel_ctn PROPERTIES
  CXX_STANDARD 17
  CXX_STANDARD_REQUIRED YES
  CXX_EXTENSIONS NO
)

if(CMAKE_BUILD_TYPE MATCHES Debug)
  target_compile_definitions(wheel_ctn PUBLIC PH_DEBUG=1)
endif()

file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/dist)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/dist/bin)

set_target_properties(wheel_ctn PROPERTIES RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/dist/bin)
set_target_properties(wheel_ctn PROPERTIES OUTPUT_NAME wheel-ctn)
