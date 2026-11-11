#include <gtest/gtest.h>

#include "lancomm/net/net.hpp"

TEST(Net, VersionIsSet) { EXPECT_FALSE(lancomm::net::version().empty()); }

TEST(Net, HostNameIsSet) { EXPECT_FALSE(lancomm::net::host_name().empty()); }
