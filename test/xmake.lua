add_requires("conan::gtest 1.12.1", {alias = "gtest"})


target("tests")
    set_filename ("gtest-run")

    set_kind ("binary")
    add_files ("*.cpp")
    add_packages ("gtest")
    set_languages ("c++11")

    set_default (false)
    set_targetdir ("$(buildir)/$(plat)/$(arch)/$(mode)/test/")
