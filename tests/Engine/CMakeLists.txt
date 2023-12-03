cmake_minimum_required(VERSION 2.8.4)
project(Engine)

set(TOP_DIR "${PROJECT_SOURCE_DIR}/../..")
set(INTERNAL_DIR  "${TOP_DIR}/internal")
set(EXTERNAL_DIR  "${TOP_DIR}/external")
set(PLATFORM_DIR  "${TOP_DIR}/platform")
set(RESOURCES_DIR "${TOP_DIR}/resources")
set(OUTPUT_DIR    "${TOP_DIR}/output/${CMAKE_PROJECT_NAME}/${CMAKE_BUILD_TYPE}")

set(library ${INTERNAL_DIR}/src/crosswind/composition/actor.cpp
            ${INTERNAL_DIR}/src/crosswind/composition/animated_actor.cpp
            ${INTERNAL_DIR}/src/crosswind/composition/text_actor.cpp
            ${INTERNAL_DIR}/src/crosswind/composition/camera.cpp
            ${INTERNAL_DIR}/src/crosswind/composition/core.cpp
            ${INTERNAL_DIR}/src/crosswind/composition/scene.cpp
            ${INTERNAL_DIR}/src/crosswind/composition/stage.cpp
            ${INTERNAL_DIR}/src/crosswind/configuration/settings.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/object/mesh.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/object/model.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/object/sprite.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/object/sprite_animation.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/object/text.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/object/vertex.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/opengl/render_batch.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/opengl/renderer.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/opengl/shader_program.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/opengl/sprite_batch.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/opengl/texture.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/opengl/window.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/sdl/font.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/sdl/surface.cpp
            ${INTERNAL_DIR}/src/crosswind/graphical/video.cpp
            ${INTERNAL_DIR}/src/crosswind/platform/application.cpp
            ${INTERNAL_DIR}/src/crosswind/platform/exception.cpp
            ${INTERNAL_DIR}/src/crosswind/platform/filesystem.cpp
            ${INTERNAL_DIR}/src/crosswind/platform/input.cpp
            ${INTERNAL_DIR}/src/crosswind/scripting/interpreter_a.cpp
            ${INTERNAL_DIR}/src/crosswind/scripting/interpreter_b.cpp
            ${INTERNAL_DIR}/src/crosswind/simulation/debug/opengl/drawer.cpp
            ${INTERNAL_DIR}/src/crosswind/simulation/debug/opengl/shader_program.cpp
            ${INTERNAL_DIR}/src/crosswind/simulation/debug/opengl/vertex.cpp
            ${INTERNAL_DIR}/src/crosswind/simulation/detail/body.cpp
            ${INTERNAL_DIR}/src/crosswind/simulation/detail/character.cpp
            ${INTERNAL_DIR}/src/crosswind/simulation/box.cpp
            ${INTERNAL_DIR}/src/crosswind/simulation/physics.cpp
            ${INTERNAL_DIR}/src/crosswind/simulation/plane.cpp
            ${INTERNAL_DIR}/src/crosswind/sound/chunk.cpp
            ${INTERNAL_DIR}/src/crosswind/sound/mixer.cpp
            ${INTERNAL_DIR}/src/crosswind/sound/music.cpp
            ${INTERNAL_DIR}/src/crosswind/engine.cpp)

set(sources ${library} main.cpp)

set(PROJECT_OUTPUT_DIRECTORY "${OUTPUT_DIR}")

add_executable(${PROJECT_NAME} ${sources})

set_target_properties(${PROJECT_NAME}
    PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/lib"
    LIBRARY_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/lib"
    RUNTIME_OUTPUT_DIRECTORY "${PROJECT_OUTPUT_DIRECTORY}/bin"
)

set(SDL2_libs        SDL2main SDL2 winmm imm32 version)
#set(SDL2_image_libs  SDL2_image jpeg png z)
set(SDL2_image_libs  SDL2_image png z)
set(SDL2_ttf_libs    SDL2_ttf freetype)
set(SDL2_mixer_libs  SDL2_mixer vorbisenc vorbisfile vorbis ogg)
set(win32_libs       winmm imm32 version)
set(bullet3_libbs    BulletDynamics BulletCollision LinearMath)
set(opengl_libs      glu32 opengl32)
set(opengl_ext_libs  glew)


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

target_link_libraries(${PROJECT_NAME} PRIVATE bullet3 chaiscript glew glm jsoncons SDL SDL_image SDL_mixer SDL_ttf)

file(COPY ${RESOURCES_DIR}/assets DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)
file(COPY ${PROJECT_SOURCE_DIR}/scripts DESTINATION  ${PROJECT_OUTPUT_DIRECTORY}/bin)