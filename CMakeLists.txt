# 指定CMake最低版本
cmake_minimum_required(VERSION 3.14)

#设置c++标准
set(CMAKE_CXX_STANDARD 11)

# 指定工程名字
project (split_words)

# 指定工程类型(共享库)以及源文件
add_library(${PROJECT_NAME} 
    STATIC 
        src/split_words.cpp
)

# 指定头文件
target_include_directories(${PROJECT_NAME}
    PUBLIC 
        ${PROJECT_SOURCE_DIR}/include
)

# 添加 pthread 依赖
if(WIN32)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE -pthread)
endif()

# 导入CPM脚本
set(CPM_DOWNLOAD_LOCATION "${CMAKE_BINARY_DIR}/cmake/CPM.cmake")
if(NOT EXISTS ${CPM_DOWNLOAD_LOCATION})
   message(STATUS "Downloading CPM.cmake")
   file(DOWNLOAD
   https://cdn.jsdelivr.net/gh/cpm-cmake/CPM.cmake/cmake/CPM.cmake
${CPM_DOWNLOAD_LOCATION})
endif(NOT EXISTS ${CPM_DOWNLOAD_LOCATION})
include(${CPM_DOWNLOAD_LOCATION})

# 导入 jsoncpp 依赖
CPMAddPackage(
    NAME jsoncpp	 
    GIT_TAG master
    GIT_REPOSITORY https://github.com/open-source-parsers/jsoncpp
    DOWNLOAD_ONLY YES
)
add_library(jsoncpp_static 
    STATIC 
        ${jsoncpp_SOURCE_DIR}/src/lib_json/json_reader.cpp
        ${jsoncpp_SOURCE_DIR}/src/lib_json/json_value.cpp
        ${jsoncpp_SOURCE_DIR}/src/lib_json/json_writer.cpp
)
target_include_directories(jsoncpp_static
    PUBLIC 
        ${jsoncpp_SOURCE_DIR}/include
)
target_include_directories(jsoncpp_static
    PRIVATE 
        ${jsoncpp_SOURCE_DIR}/src/lib_json
)
target_link_libraries(${PROJECT_NAME} PRIVATE jsoncpp_static)

# 导入 httplib 依赖
CPMAddPackage(
    NAME httplib	 
    GIT_TAG master
    GIT_REPOSITORY https://hub.fastgit.org/yhirose/cpp-httplib
    DOWNLOAD_ONLY YES
)
target_include_directories(${PROJECT_NAME} PRIVATE ${httplib_SOURCE_DIR})
if(WIN32)
  target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
endif()

# 添加测试
add_executable(test 
    test/test.cpp)
target_link_libraries(test PRIVATE split_words)

