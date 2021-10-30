file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/dist)
file(MAKE_DIRECTORY ${CMAKE_BINARY_DIR}/dist/res)

file (GLOB_RECURSE WHEEL_CTN_RES LIST_DIRECTORIES false "${CMAKE_SOURCE_DIR}/res/*")
add_custom_target(wheel_ctn_res ALL DEPENDS ${WHEEL_CTN_RES})

foreach(RES_FILE ${WHEEL_CTN_RES})
  get_filename_component(FILE_NAME ${RES_FILE} NAME)
  set(FILE_NAME "${CMAKE_BINARY_DIR}/dist/res/${FILE_NAME}")
  configure_file(${RES_FILE} ${FILE_NAME} COPYONLY)
endforeach()

add_dependencies(wheel_ctn wheel_ctn_res)
