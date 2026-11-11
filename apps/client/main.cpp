#include <cstdint>
#include <string>

#include <CLI/CLI.hpp>
#include <spdlog/spdlog.h>

#include "lancomm/net/net.hpp"

int main(int argc, char** argv) {
    CLI::App app{"lan-comm client"};
    std::string host;
    std::uint16_t port = 50555;
    app.add_option("host", host, "Server IP or host name")->required();
    app.add_option("-p,--port", port, "Server TCP port");
    CLI11_PARSE(app, argc, argv);

    spdlog::info("lan-comm client v{} on host '{}'", lancomm::net::version(),
                 lancomm::net::host_name());
    spdlog::info("(Phase 1 skeleton) would connect to {}:{}", host, port);
    return 0;
}
