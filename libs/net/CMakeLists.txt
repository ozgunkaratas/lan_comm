add_library(lancomm_net
    src/net.cpp
)
add_library(lancomm::net ALIAS lancomm_net)

target_include_directories(lancomm_net PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
)
target_link_libraries(lancomm_net PUBLIC asio::asio)
target_compile_definitions(lancomm_net PUBLIC LANCOMM_VERSION="${PROJECT_VERSION}")
lancomm_set_warnings(lancomm_net)

if(WIN32)
    # Asio needs Winsock; must also reach consumers' compile units
    target_compile_definitions(lancomm_net PUBLIC _WIN32_WINNT=0x0A00)
    target_link_libraries(lancomm_net PUBLIC ws2_32 mswsock)
endif()
