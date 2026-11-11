#include <cstdint>

#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>

#include "lancomm/net/net.hpp"

int main(int argc, char** argv) {
    CLI::App app{"lan-comm server"};
    std::uint16_t port = 50555;
    app.add_option("-p,--port", port, "TCP port to listen on");
    CLI11_PARSE(app, argc, argv);

    spdlog::info("lan-comm server v{} on host '{}'", lancomm::net::version(),
                 lancomm::net::host_name());
    for (const auto& addr : lancomm::net::local_addresses()) {
        spdlog::info("  local address: {}", addr);
    }
    spdlog::info("(Phase 1 skeleton) would listen on port {}", port);
    return 0;
}
