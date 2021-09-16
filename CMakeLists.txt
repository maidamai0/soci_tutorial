cmake_minimum_required(VERSION 3.20)
get_filename_component(_name ${CMAKE_CURRENT_LIST_DIR} NAME)
project(${_name})

set(CMAKE_CXX_STANDARD 17)
set(CXX_STANDARD_REQUIRED ON)

find_package(SOCI CONFIG REQUIRED)
link_libraries(SOCI::soci_core_static SOCI::soci_odbc_static SOCI::soci_empty_static SOCI::soci_sqlite3_static)

file(GLOB srcs "src/*.cpp")

foreach(src ${srcs})
  get_filename_component(_app ${src} NAME_WLE)
  add_executable(${_app} ${src})
  target_precompile_headers(${_app} PRIVATE src/pch.h)
endforeach()
