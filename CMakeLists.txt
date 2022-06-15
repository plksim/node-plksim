cmake_minimum_required(VERSION 3.9)
cmake_policy(SET CMP0042 NEW)
project("node-plksim")

set(CMAKE_CXX_STANDARD 11)

message("[***] CMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}")
message("[***] CMAKE_SYSTEM_PROCESSOR=${CMAKE_SYSTEM_PROCESSOR}")
message("[***] CMAKE_INSTALL_PREFIX=${CMAKE_INSTALL_PREFIX}")

file(GLOB SOURCE_FILES "src/binding.cc")

# Node library
add_library(${PROJECT_NAME} SHARED ${SOURCE_FILES} ${CMAKE_JS_SRC})
set_target_properties(${PROJECT_NAME} PROPERTIES PREFIX "" SUFFIX ".node")
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_JS_INC})
target_link_libraries(${PROJECT_NAME} ${CMAKE_JS_LIB})

# Link native library
find_package(plksim REQUIRED)
message("PLKSIM_VERSION=${PLKSIM_VERSION}")
target_include_directories(${PROJECT_NAME} PRIVATE ${PLKSIM_INCLUDE_DIRS})
target_link_directories(${PROJECT_NAME} PRIVATE ${PLKSIM_LIBRARY_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PLKSIM_LIBRARIES})

# Include Node-API C++ wrappers
execute_process(COMMAND node -p "require('node-addon-api').include"
    WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
    OUTPUT_VARIABLE NODE_ADDON_API_DIR
    )
string(REGEX REPLACE "[\r\n\"]" "" NODE_ADDON_API_DIR ${NODE_ADDON_API_DIR})
target_include_directories(${PROJECT_NAME} PRIVATE ${NODE_ADDON_API_DIR})

# define NAPI_VERSION
add_compile_definitions(NAPI_VERSION=3)