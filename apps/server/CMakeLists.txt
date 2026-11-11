add_executable(lancomm_server main.cpp)
target_link_libraries(lancomm_server PRIVATE lancomm::net lancomm::log CLI11::CLI11)
lancomm_set_warnings(lancomm_server)
