#!/bin/env python
import re
from glob import glob

from jinja2 import Template
from itertools import chain


# LINUX + g++

conf = {
    "CXXFLAGS": "-std=c++20 -Wall -fmodules-ts",
    "MODULE_DIR": "gcm.cache",
    "STD_MODULE_DIR": "$(MODULE_DIR)/usr/include/c++/$(shell g++ --version | grep g++ | awk '{print $$3}')",
    "MODULE_MODULE": "$(MODULE_DIR)/dyno.gcm",
}

std_headers = set()

modules = []
for s in glob("src/*.cpp"):
    with open(s) as f:
        source = f.read()
        for m in re.findall("export module ([a-z.]*);", source):
            module = {}
            module["name"] = m
            module["file"] = s
            module["source"] = re.sub(
                r"src/([a-z_]+)\.cpp", r"$(SOURCE_DIR)/\1.cpp", module["file"]
            )
            module["path"] = f"$(MODULE_DIR)/{m}.gcm"
            module["object"] = re.sub(
                r"src/([a-z_]+)\.cpp", r"$(BUILD_DIR)/\1.o", module["file"]
            )
            module["dependencies"] = {"std": [], "modules": []}
            for sh in re.findall(r"import <([a-z]+)>;", source):
                std_headers.add(sh)
                module["dependencies"]["std"].append(f"$(STD_MODULE_DIR)/{sh}.gcm")
            for sm in re.findall(r"import ([a-z.]+);", source):
                module["dependencies"]["modules"].append(f"$(MODULE_DIR)/{sm}.gcm")

            modules.append(module)


def get_obj_dependencies(path, modules):

    return list(
        set(
            list(
                chain.from_iterable(
                    [
                        [module["object"]]
                        + list(
                            chain.from_iterable(
                                [
                                    get_obj_dependencies(sm, modules)
                                    for sm in module["dependencies"]["modules"]
                                ]
                            )
                        )
                        for module in modules
                        if module["path"] == path
                    ]
                )
            )
        )
    )


obj_list = list(
    chain.from_iterable(
        [
            get_obj_dependencies(m["path"], modules)
            for m in modules
            if m["path"] == conf["MODULE_MODULE"]
        ]
    )
)


tests = []
for t in glob("tests/*.cpp"):
    with open(t) as f:
        source = f.read()
        test = {}
        test["file"] = t
        test["source"] = re.sub(
            r"tests/([a-z_]+)\.cpp", r"$(TEST_SOURCE_DIR)/\1.cpp", test["file"]
        )
        test["object"] = re.sub(
            r"tests/([a-z_]+)\.cpp", r"$(TEST_BUILD_DIR)/\1.o", test["file"]
        )
        test["bin"] = re.sub(
            r"tests/([a-z_]+)\.cpp", r"$(TEST_TARGET_DIR)/\1", test["file"]
        )
        test["dependencies"] = {"std": [], "modules": [], "objects": []}
        for sh in re.findall(r"import <([a-z]+)>;", source):
            std_headers.add(sh)
            test["dependencies"]["std"].append(f"$(STD_MODULE_DIR)/{sh}.gcm")
        for sm in re.findall(r"import ([a-z.]+);", source):
            test["dependencies"]["modules"].append(f"$(MODULE_DIR)/{sm}.gcm")

        tests.append(test)

std_headers = [
    {"name": sh, "path": f"$(STD_MODULE_DIR)/{sh}.gcm"} for sh in std_headers
]

t = Template(open("Makefile.jinja", "r").read())

open("Makefile", "w").write(
    t.render(
        conf=conf,
        modules=modules,
        tests=tests,
        std_headers=std_headers,
        obj_list=obj_list,
    )
)
