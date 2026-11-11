find_package(GTest REQUIRED)

add_executable(lancomm_tests test_net.cpp)
target_link_libraries(lancomm_tests PRIVATE lancomm::net GTest::gtest_main)
lancomm_set_warnings(lancomm_tests)

include(GoogleTest)
gtest_discover_tests(lancomm_tests)
