# 导入CPM脚本
include(cmake/CPM.cmake)

# 导入jsoncpp依赖
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

# 指定头文件
target_include_directories(jsoncpp_static
    PUBLIC 
        ${jsoncpp_SOURCE_DIR}/include
)

# 指定头文件
target_include_directories(jsoncpp_static
    PRIVATE 
        ${jsoncpp_SOURCE_DIR}/src/lib_json
)

