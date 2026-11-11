# lan-comm

Messaging and file retrieval/analysis between two hosts on a local network.
C++20, Asio, Conan 2 + CMake, Windows and Linux.

## Build

The recipe extends the shared `cmake-base` recipe in `../conan-base`.
Register it once per machine (and after every change to it):
```bash
conan create ../conan-base
```
## Profiles

Install profiles to cover your release/debug.
```bash
conan install . -pr:a profiles/windows-msvc
conan install . -pr:a profiles/windows-msvc-debug
```

Default build (any OS, any profile, no tests, all deps header-only):
```bash
conan build .
```

Additions via `-o` / `-s` / `-pr`:
```bash
# with tests (gtest is compiled, so add --build=missing)
conan build . -o with_tests=True --build=missing

# debug
conan build . -s build_type=Debug

# project profiles (C++20 pinned)
conan build . -pr:a profiles/linux-gcc
conan build . -pr:a profiles/windows-msvc
conan build . -pr:a profiles/windows-msvc-debug
```

Binaries land in `build/Release/apps/...` (Linux) or `build/apps/.../Release` (Windows).
For IDE work: `conan install .` then `cmake --preset conan-default` (Windows) or
`conan-release` (Linux).

## Run

```bash
lancomm_server --port 50555
lancomm_client <server-ip> --port 50555
```

## Layout

```
libs/net/        transport layer (Asio)
libs/protocol/   framing + message types           (Phase 3)
libs/files/      file catalogue + transfer          (Phase 6)
libs/analysis/   timestamps, hashes, content checks (Phase 7)
apps/server/     server executable
apps/client/     client executable
tests/           GoogleTest unit + loopback tests
profiles/        Conan profiles
```

## Roadmap

| Phase | Goal | Exit criterion |
|------:|------|----------------|
| 0 | Network sanity: same subnet, no AP isolation, firewall rule | `nc`/`Test-NetConnection` works both ways |
| 1 | Skeleton: Conan 2, CMake, profiles, warnings, tests | Builds and tests pass on both OSes ✅ (Linux verified) |
| 2 | TCP link with Asio: sync echo server/client | Echo between the two machines |
| 3 | Protocol: length-prefixed frames, little-endian header, versioned handshake; messages `Hello`, `Chat`, `ListFiles`, `FileInfo`, `GetFile`, `FileChunk`, `Error` | Round-trip unit tests for every message |
| 4 | Async + robustness: C++20 coroutines, timeouts, heartbeat, reconnect, Ctrl+C shutdown | Survives Wi-Fi drop and reconnects |
| 5 | Messaging: bidirectional chat, simple console UI | Chat between both hosts |
| 6 | File retrieval: server exposes a sandboxed root dir (no path traversal), chunked transfer, SHA-256 verify, resume | Large file arrives with matching hash |
| 7 | Analysis: timestamps (mtime/ctime, sender vs. receiver clock), size, hash, type sniffing (magic bytes), text stats/search, report output (console/JSON) | `analyze <file>` produces a report, local or remote |
| 8 | Discovery: UDP broadcast announce | Client finds server without an IP |
| 9 | Security: TLS (OpenSSL) with cert pinning or PSK | Traffic encrypted, unknown peers rejected |
| 10 | Quality: GitHub Actions (MSVC + GCC), clang-tidy, ASan/UBSan, `conan create` | Green CI matrix |
