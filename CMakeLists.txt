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

if(WIN32)
else()
    target_link_libraries(${PROJECT_NAME} PRIVATE -pthread)
endif()

include(cmake/CPM.cmake)

CPMAddPackage(
    NAME httplib	 
    GIT_TAG master
    GIT_REPOSITORY https://hub.fastgit.org/yhirose/cpp-httplib
    DOWNLOAD_ONLY YES
)
target_include_directories(${PROJECT_NAME} PRIVATE ${httplib_SOURCE_DIR})

# 链接win socket
if(WIN32)
  target_link_libraries(${PROJECT_NAME} PRIVATE ws2_32)
endif()

# 导入jsoncpp依赖
include(cmake/jsoncpp.cmake)
target_link_libraries(${PROJECT_NAME} PRIVATE jsoncpp_static)

add_executable(test 
    test/test.cpp)
target_link_libraries(test PRIVATE split_words)
