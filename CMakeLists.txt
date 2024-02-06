# 设置项目名称
project(Http_Encapsulate)

# 设置最低的CMake版本
cmake_minimum_required(VERSION 3.10)

# 设置项目版本信息
set(CMAKE_PROJECT_VERSION 1.2.3)  # 项目的完整版本号
set(CMAKE_PROJECT_VERSION_MAJOR 1) # 主版本号
set(CMAKE_PROJECT_VERSION_MINOR 2) # 次版本号
set(CMAKE_PROJECT_VERSION_PATCH 3) # 补丁版本号

# Enable C++11
set(CMAKE_CXX_STANDARD 14)


SET(CMAKE_BUILD_TYPE "Debug")
SET(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
SET(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

SET(GoogleTest  ${CMAKE_CURRENT_SOURCE_DIR}/third_party/googletest)
SET(Spdlog        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/spdlog)
SET(RapidJson   ${CMAKE_CURRENT_SOURCE_DIR}/third_party/rapidjson)
SET(Libevent    ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libevent)
SET(Pcap        ${CMAKE_CURRENT_SOURCE_DIR}/third_party/libpcap)


add_subdirectory(${Spdlog})
add_subdirectory(${GoogleTest})
add_subdirectory(${RapidJson})
add_subdirectory(${Pcap})

# libevent
find_library(LIBEVENT_LIBRARIES
    NAMES event
    NAMES event_core
    NAMES event_pthreads
    PATHS ${LIBEVENT_ROOT}/lib
)

include_directories(${CMAKE_PROJECT_NAME} PUBLIC 
    include
    ${Spdlog}/include
    ${GoogleTest}/googletest/include
    ${GoogleTest}/googlemock/include
    ${RapidJson}/include
    ${libevent}/include
    ${libpcap}/pcap
)

# 添加源文件
aux_source_directory(${PROJECT_SOURCE_DIR}/src SOURCES)



add_executable(${CMAKE_PROJECT_NAME}_TEST
    ${CMAKE_SOURCE_DIR}/test/json_parse_test.cpp)

add_library(${CMAKE_PROJECT_NAME}_lib ${SOURCES})

target_link_libraries(${CMAKE_PROJECT_NAME}_lib
    spdlog
    gtest
    gmock
    gtest_main
    gmock_main
    event 
    event_core 
    event_pthreads 
    pcap 
)

target_link_libraries(${CMAKE_PROJECT_NAME}_TEST 
    ${CMAKE_PROJECT_NAME}_lib
    gtest
    gmock
    gtest_main
    gmock_main
)

# 如果有其他的子目录，可以继续使用 add_subdirectory 添加
# add_subdirectory(another_subdirectory)

# 如果有测试目录，可以启用测试
# enable_testing()
# add_subdirectory(test)

# 设置C++标准
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

