from conan import ConanFile


class LanCommConan(ConanFile):
    name = "lan-comm"
    version = "0.1.0"
    description = "LAN messaging and file retrieval/analysis between two hosts"

    # Layout, toolchain, build, CTest run, package() and the `with_tests`
    # option come from the shared base in ../conan-base.
    python_requires = "cmake-base/[>=1.0 <2]"
    python_requires_extend = "cmake-base.CMakeAppBase"

    # Default build must succeed with a plain `conan build .` on any profile:
    # tests off (base default), and every dependency header-only (no binaries
    # to download/build). with_tests' default is merged in by the base.
    default_options = {
        "spdlog/*:header_only": True,
        "fmt/*:header_only": True,
    }

    def requirements(self):
        self.requires("asio/1.30.2")
        self.requires("spdlog/1.14.1")
        self.requires("cli11/2.4.2")

    def build_requirements(self):
        if self.options.with_tests:
            self.test_requires("gtest/1.15.0")

    def configure_toolchain(self, tc):
        super().configure_toolchain(tc)
        # CMakeLists.txt switches tests with its own option name.
        tc.cache_variables["LANCOMM_BUILD_TESTS"] = bool(self.options.with_tests)
