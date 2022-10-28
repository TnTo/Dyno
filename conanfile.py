from conans import ConanFile, tools
from conan.tools.cmake import CMake, CMakeToolchain, CMakeDeps, cmake_layout


class Pkg(ConanFile):

    name = 'Dyno'
    version = '0.0.1'
    license = 'MIT'
    author = "Michele Ciruzzi tnto@hotmail.it"
    url = 'https://www.github.com/TnTo/Dyno'
    settings = 'os', 'compiler', 'build_type', 'arch'
    description = 'Dyno - A library for AB-SFC models'
    options = {"shared": [True, False], "fPIC": [
        True, False], "test": [True, False]}
    default_options = {"shared": False, "fPIC": True, "test": False}
    exports_sources = 'src/*'

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

        if self.settings.compiler == "Visual Studio":
            self.settings.compiler.cppstd = '20'
        else:
            self.settings.compiler.cppstd = 'gnu20'

        self.settings.compiler.libcxx = "libstdc++11"

    def layout(self):
        cmake_layout(self, build_folder='build')

    def generate(self):
        tc = CMakeToolchain(self)
        tc.generate()
        deps = CMakeDeps(self)
        deps.generate()

    def package(self):
        self.copy('*.h', dst='include', src='src')
        self.copy('*.h', dst='include/Dyno', src='src/Dyno')

    def package_info(self):
        self.cpp_info.libs = ['Dyno']
