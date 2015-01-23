cmake_minimum_required(VERSION 2.8.4)
project(websockets)


set(INCLUDE_LIBRARY_PATH "${PROJECT_SOURCE_DIR}/../include")

set(EXTERNAL_LIBRARY_PATH "${PROJECT_SOURCE_DIR}/../3rdparty")

set(PROJECT_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/output/${CMAKE_PROJECT_NAME}/${CMAKE_BUILD_TYPE}")


include_directories(${INCLUDE_LIBRARY_PATH}
                    ${EXTERNAL_LIBRARY_PATH}/asio/include)

link_directories(${BUILD_LIBRARY_PATH}/lib)


if( CMAKE_BUILD_TYPE STREQUAL "Debug")

add_compile_options(-std=c++1y -g -DASIO_STANDALONE -DASIO_SEPARATE_COMPILATION)

endif( CMAKE_BUILD_TYPE STREQUAL "Debug" )

if( CMAKE_BUILD_TYPE STREQUAL  "Release" )

endif( CMAKE_BUILD_TYPE STREQUAL  "Release" )


file(GLOB sources main.cpp)


add_executable(websockets ${sources})

set_target_properties(websockets
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/bin"
)

target_link_libraries (websockets)