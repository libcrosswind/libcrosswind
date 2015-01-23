cmake_minimum_required(VERSION 2.8.4)
project(game)


set(INCLUDE_LIBRARY_PATH    "${PROJECT_SOURCE_DIR}/../../internal/include"
                            "${PROJECT_SOURCE_DIR}/../../external/CImg-1.6.0/include")

set(PROJECT_OUTPUT_DIRECTORY "${PROJECT_SOURCE_DIR}/../../output/${CMAKE_PROJECT_NAME}/${CMAKE_BUILD_TYPE}")


include_directories(${INCLUDE_LIBRARY_PATH})

if( CMAKE_BUILD_TYPE STREQUAL "Debug")

add_compile_options(-std=gnu++1y -g)

elseif( CMAKE_BUILD_TYPE STREQUAL "Release")

add_compile_options(-std=c++1y)

endif()

file(GLOB sources main.cpp)


add_executable(game ${sources})

set_target_properties(game
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/bin"
)

target_link_libraries (game)

file(COPY ${PROJECT_SOURCE_DIR}/assets/ball.png ${PROJECT_SOURCE_DIR}/assets/paddle.png DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)