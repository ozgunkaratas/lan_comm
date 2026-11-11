#pragma once

#include <string>
#include <string_view>
#include <vector>

namespace lancomm::net {

/// Library version string (from CMake project version).
[[nodiscard]] std::string_view version() noexcept;

/// Host name of this machine.
[[nodiscard]] std::string host_name();

/// IPv4/IPv6 addresses this host resolves to. Useful for the Phase 0
/// check: run on both machines and confirm they share a subnet.
[[nodiscard]] std::vector<std::string> local_addresses();

}  // namespace lancomm::net
