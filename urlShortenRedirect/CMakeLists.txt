cmake_minimum_required(VERSION 3.9)
project(main)

find_package(OpenSSL REQUIRED)
find_package(cpprestsdk REQUIRED)

INCLUDE_DIRECTORIES(${Boost_INCLUDE_DIRS} ${OPENSSL_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS On)

add_executable(main main.cpp)
target_link_libraries(main PRIVATE cpprestsdk::cpprest)