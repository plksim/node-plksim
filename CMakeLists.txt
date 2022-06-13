cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0042 NEW)
project("node-plksim")

set(CMAKE_CXX_STANDARD 11)

message("[***] CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}")
message("[***] CMAKE_SYSTEM_PROCESSOR=${CMAKE_SYSTEM_PROCESSOR}")
message("[***] CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")

include_directories(${CMAKE_JS_INC})

file(GLOB SOURCE_FILES "src/binding.cc")

add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

# Link native library
target_include_directories(${PROJECT_NAME} PRIVATE "${CMAKE_INSTALL_PREFIX}/include")
target_link_directories(${PROJECT_NAME} PRIVATE "${CMAKE_INSTALL_PREFIX}/lib")
target_link_libraries(${PROJECT_NAME} PRIVATE plksim)

# Include Node-API wrappers
execute_process(COMMAND node -p "require('node-addon-api').include"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE NODE_ADDON_API_DIR
    )
string(REGEX REPLACE "[\r\n\"]" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})

target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})

# define NAPI_VERSION
add_compile_definitions(NAPI_VERSION=3)