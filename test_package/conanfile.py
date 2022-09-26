from conans import ConanFile
import os
import multiprocessing as mp


class PkgTest(ConanFile):
    settings = 'os', 'compiler', 'build_type', 'arch', 'build_type'
    requires = ['Dyno/0.0.1', 'catch2/3.1.0']
    options = {"test": [True, False]}
    default_options = {"test": True}
    generators = 'scons'

    def build(self):
        test = "--test" if (self.options.test) else ''
        debug = "--debug-mode" if (self.settings.build_type == "Debug") else ''
        self.run('scons -C {} -j {} {} {}'.format(self.source_folder,
                 int(mp.cpu_count() * 1.5), test, debug))

    def test(self):
        self.run(os.path.join('.', 'test'))
