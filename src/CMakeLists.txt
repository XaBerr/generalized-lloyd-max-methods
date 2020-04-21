file(
  GLOB
  HEADER_LISTCONFIGURE_DEPENDS
  "${PROJECT_SOURCE_DIR}/include/${PROJECT_NAME}/*.h"
)
add_library(
  ${PROJECT_NAME}
  INTERFACE
)
target_include_directories(
  ${PROJECT_NAME}
  INTERFACE
  ../include
)

