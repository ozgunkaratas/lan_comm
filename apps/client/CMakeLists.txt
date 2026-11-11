add_executable(lancomm_client main.cpp)
target_link_libraries(lancomm_client PRIVATE lancomm::net lancomm::log CLI11::CLI11)
lancomm_set_warnings(lancomm_client)
