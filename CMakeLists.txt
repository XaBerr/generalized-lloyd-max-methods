cmake_minimum_required(VERSION 3.14)

project(
  "LGB-methods"
  VERSION 1.0.0
  DESCRIPTION "In this repository there are various implementations of the Linde, Buzo, and Gray algorithm (generalize Lloyd-Max algorithm) for the calculation of vector quantizer."
  LANGUAGES CXX
)

if(CMAKE_PROJECT_NAME STREQUAL PROJECT_NAME)
  set(CMAKE_CXX_STANDARD 11)
  set(CMAKE_CXX_STANDARD_REQUIRED ON)
  set(CMAKE_CXX_EXTENSIONS OFF)
  set_property(GLOBAL PROPERTY USE_FOLDERS ON)
  add_subdirectory(apps)
  add_subdirectory(tests)
endif()

add_subdirectory(src)
