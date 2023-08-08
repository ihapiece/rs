cmake_minimum_required(VERSION 3.21)
project(rs LANGUAGES CXX)

include(FetchContent)
FetchContent_Declare(SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 2.6.x)
FetchContent_MakeAvailable(SFML)

file(GLOB_RECURSE sources CONFIGURE_DEPENDS "src/*.cpp")
add_executable(rs ${sources})

target_link_libraries(rs PRIVATE sfml-graphics)
target_compile_features(rs PRIVATE cxx_std_17)
if (WIN32 AND BUILD_SHARED_LIBS)
    add_custom_command(TARGET rs POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy $<TARGET_RUNTIME_DLLS:rs> $<TARGET_FILE_DIR:rs> COMMAND_EXPAND_LISTS)
endif()

install(TARGETS rs)