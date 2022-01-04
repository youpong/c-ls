#include "file.h"
#include "util.h"

static void test_foo() {
    expect_str(__LINE__, "dir/", basedir("dir/name"));
    expect_str(__LINE__, "dir/", basedir("dir/"));
    expect_str(__LINE__, "/",    basedir("/name"));
    expect_str(__LINE__, "",     basedir("name"));
    expect_str(__LINE__, "",     basedir(""));
}

void run_file_test() {
    test_foo();
}




