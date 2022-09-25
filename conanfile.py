from conans import ConanFile, tools


class Pkg(ConanFile):

    name = 'Dyno'
    version = '0.0.1'
    license = 'MIT'
    author = "Michele Ciruzzi tnto@hotmail.it"
    url = 'https://www.github.com/TnTo/Dyno'
    settings = 'os', 'compiler', 'cppstd', 'build_type', 'arch'
    description = 'Dyno - A library for AB-SFC models'
    options = {"shared": [True, False], "fPIC": [True, False]}
    default_options = {"shared": False, "fPIC": True}
    exports_sources = 'src/*'
    generators = 'scons'

    def config_options(self):
        if self.settings.os == "Windows":
            del self.options.fPIC

        if self.settings.compiler == "Visual Studio":
            self.settings.cppstd = '17'
        else:
            self.settings.cppstd = 'gnu17'

    def build(self):
        debug_opts = [
            '--debug-build'] if self.settings.build_type == 'Debug' else []
        tools.mkdir("build")
        with tools.chdir("build"):
            self.run(
                ['scons', '-C', '{}/src'.format(self.source_folder)] + debug_opts)

    def package(self):
        self.copy('*.h', 'include', src='src')
        self.copy('*.lib', 'lib', keep_path=False)
        self.copy('*.a', 'lib', keep_path=False)

    def package_info(self):
        self.cpp_info.libs = ['Dyno']
