cmake_minimum_required(VERSION 3.23)
project(lan-comm VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

option(LANCOMM_BUILD_TESTS "Build unit tests" OFF)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")
include(CompilerWarnings)

find_package(asio REQUIRED)
find_package(spdlog REQUIRED)
find_package(CLI11 REQUIRED)

# spdlog's target name depends on its header_only option:
# header-only -> spdlog::spdlog_header_only, compiled -> spdlog::spdlog.
add_library(lancomm_log INTERFACE)
if(TARGET spdlog::spdlog_header_only)
    target_link_libraries(lancomm_log INTERFACE spdlog::spdlog_header_only)
else()
    target_link_libraries(lancomm_log INTERFACE spdlog::spdlog)
endif()
add_library(lancomm::log ALIAS lancomm_log)

add_subdirectory(libs/net)
add_subdirectory(apps/server)
add_subdirectory(apps/client)

# Used by `conan create` (the base recipe's package() step).
install(TARGETS lancomm_server lancomm_client RUNTIME DESTINATION bin)

if(LANCOMM_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()
