from conans import ConanFile, tools
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout
import os


class PkgTest(ConanFile):
    settings = 'os', 'compiler', 'build_type', 'arch'
    requires = ['Dyno/0.0.1', 'catch2/3.1.0']

    def config_options(self):
        if self.settings.compiler == "Visual Studio":
            self.settings.compiler.cppstd = '20'
        else:
            self.settings.compiler.cppstd = 'gnu20'

        self.settings.compiler.libcxx = "libstdc++11"
        self.settings.build_type = 'Debug'

    def layout(self):
        cmake_layout(self, build_folder='build')

    def generate(self):
        tc = CMakeToolchain(self)
        tc.variables['DYNO_PATH'] = self.deps_cpp_info["Dyno"].rootpath
        tc.variables['ROOT_DIR'] = os.path.abspath(
            os.path.join(self.source_folder, os.pardir))
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def build(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.build()

    def test(self):
        cmake = CMake(self)
        cmake.configure()
        cmake.test()
