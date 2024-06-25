# CMakeList.txt : CMake project for PrimeTD1, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

# Enable Hot Reload for MSVC compilers if supported.
if (POLICY CMP0141)
  cmake_policy(SET CMP0141 NEW)
  set(CMAKE_MSVC_DEBUG_INFORMATION_FORMAT "$<IF:$<AND:$<C_COMPILER_ID:MSVC>,$<CXX_COMPILER_ID:MSVC>>,$<$<CONFIG:Debug,RelWithDebInfo>:EditAndContinue>,$<$<CONFIG:Debug,RelWithDebInfo>:ProgramDatabase>>")
endif()

project (SDLTest)

#vcpkg install imgui entt sdl2 sdl2-ttf
aux_source_directory(src SRC)
include_directories($ENV{VCPKG_ROOT}/installed/x64-windows/include)

add_executable(SDLTest ${SRC})

target_include_directories(SDLTest PRIVATE include)
target_link_directories(SDLTest PRIVATE $ENV{VCPKG_ROOT}/installed/x64-windows/lib)
if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET SDLTest PROPERTY CXX_STANDARD 17)
endif()

target_link_libraries(SDLTest SDL2.lib SDL2_image.lib)

# TODO: Add tests and install targets if needed.
