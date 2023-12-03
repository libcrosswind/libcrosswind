cmake_minimum_required(VERSION 2.8.4)

set(CMAKE_CXX_STANDARD 20)


project(Engine)

set(PROJECT_NAME Engine)

set(TOP_DIR ${CMAKE_CURRENT_LIST_DIR})
set(INTERNAL_DIR  "${TOP_DIR}/internal")
set(EXTERNAL_DIR  "${TOP_DIR}/external")
set(PLATFORM_DIR  "${TOP_DIR}/platform")
set(RESOURCES_DIR "${TOP_DIR}/resources")
set(OUTPUT_DIR    "${TOP_DIR}/output/${CMAKE_PROJECT_NAME}/${CMAKE_BUILD_TYPE}")

file(GLOB_RECURSE library
       ${INTERNAL_DIR}/include/crosswind/*.hpp
       ${INTERNAL_DIR}/src/crosswind/*.cpp)

file(GLOB_RECURSE example
    ${TOP_DIR}/src/*.cpp
    ${TOP_DIR}/src/*.hpp)

set(sources ${library} ${example})

set(PROJECT_OUTPUT_DIRECTORY "${OUTPUT_DIR}")

# set(SDL2_libs        SDL2main SDL2 winmm imm32 version)
# #set(SDL2_image_libs  SDL2_image jpeg png z)
# set(SDL2_image_libs  SDL2_image png z)
# set(SDL2_ttf_libs    SDL2_ttf freetype)
# set(SDL2_mixer_libs  SDL2_mixer vorbisenc vorbisfile vorbis ogg)
# set(win32_libs       winmm imm32 version)
# set(bullet3_libbs    BulletDynamics BulletCollision LinearMath)
# set(opengl_libs      glu32 opengl32)
# set(opengl_ext_libs  glew)


add_subdirectory(${EXTERNAL_DIR}/bullet3)
add_subdirectory(${EXTERNAL_DIR}/chaiscript)
add_subdirectory(${EXTERNAL_DIR}/glew_cmake)
add_subdirectory(${EXTERNAL_DIR}/glm)
add_subdirectory(${EXTERNAL_DIR}/jsoncons)
add_subdirectory(${EXTERNAL_DIR}/sdl2/SDL)
add_subdirectory(${EXTERNAL_DIR}/sdl2/SDL_image)
add_subdirectory(${EXTERNAL_DIR}/sdl2/SDL_mixer)
add_subdirectory(${EXTERNAL_DIR}/sdl2/SDL_ttf)

set(INCLUDE_LIBRARY_PATH    "${PROJECT_SOURCE_DIR}"
                            "${INTERNAL_DIR}/include"
                            "${EXTERNAL_DIR}/jsoncons/includes"
                            "${EXTERNAL_DIR}/bullet3/src")



if(APPLE)

    #Get a list of all of the files in the data-folder
    file(GLOB_RECURSE ASSETS ${RESOURCES_DIR}/assets)
    file(GLOB_RECURSE SCRIPTS ${PROJECT_SOURCE_DIR}/scripts)

    #Add our executable, and all of the files as "Source Files"
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${sources} ${ASSETS} ${SCRIPTS})

    #individually set the file's path properties
    foreach(RES_FILE ${ASSETS})

    #Get the relative path from the data-folder to the particular file
    file(RELATIVE_PATH RES_PATH "${RESOURCES_DIR}/assets" ${RES_FILE})

    #Set it's location inside the app package (under Resources)
    set_property(SOURCE ${RES_FILE} PROPERTY MACOSX_PACKAGE_LOCATION "Resources/${RES_PATH}")

    endforeach(RES_FILE)

    #individually set the file's path properties
    foreach(RES_FILE ${SCRIPTS})

    #Get the relative path from the data-folder to the particular file
    file(RELATIVE_PATH RES_PATH "${PROJECT_SOURCE_DIR}/scripts" ${RES_FILE})

    #Set it's location inside the app package (under Resources)
    set_property(SOURCE ${RES_FILE} PROPERTY MACOSX_PACKAGE_LOCATION "Resources/${RES_PATH}")

    endforeach(RES_FILE)

else()

    file(COPY  DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)
    file(COPY ${PROJECT_SOURCE_DIR}/scripts DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)

    add_executable(${PROJECT_NAME} PRIVATE ${sources})
endif()

target_include_directories(${PROJECT_NAME} PRIVATE ${TOP_DIR}/src)

target_include_directories(${PROJECT_NAME} PRIVATE ${INTERNAL_DIR}/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${EXTERNAL_DIR}/tileson/single_include)
target_include_directories(${PROJECT_NAME} PRIVATE ${EXTERNAL_DIR}/sdl2/SDL/include)
target_include_directories(${PROJECT_NAME} PRIVATE ${EXTERNAL_DIR}/sdl2/SDL_image/include/SDL3_image)
target_include_directories(${PROJECT_NAME} PRIVATE ${EXTERNAL_DIR}/sdl2/SDL_mixer/include/SDL3_mixer)
target_include_directories(${PROJECT_NAME} PRIVATE ${EXTERNAL_DIR}/sdl2/SDL_ttf/include/SDL3_ttf)

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/bin"
)

target_link_libraries(${PROJECT_NAME} PRIVATE BulletDynamics BulletCollision LinearMath chaiscript libglew_static glm jsoncons SDL3-static SDL3_image-static SDL3_mixer-static SDL3_ttf-static)
