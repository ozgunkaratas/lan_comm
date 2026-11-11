#include "lancomm/net/net.hpp"

#include <algorithm>

#include <asio.hpp>

namespace lancomm::net {

std::string_view version() noexcept { return LANCOMM_VERSION; }

std::string host_name() { return asio::ip::host_name(); }

std::vector<std::string> local_addresses() {
    asio::io_context io;
    asio::ip::tcp::resolver resolver{io};

    std::vector<std::string> out;
    std::error_code ec;
    const auto results = resolver.resolve(host_name(), "", ec);
    if (ec) {
        return out;
    }
    for (const auto& entry : results) {
        auto addr = entry.endpoint().address().to_string();
        if (std::find(out.begin(), out.end(), addr) == out.end()) {
            out.push_back(std::move(addr));
        }
    }
    return out;
}

}  // namespace lancomm::net
