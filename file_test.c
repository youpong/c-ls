#include "file.h"
#include "util.h"

static void test_basedir() {
    expect_str(__LINE__, "dir/", basedir("dir/name"));
    expect_str(__LINE__, "dir/", basedir("dir/"));
    expect_str(__LINE__, "/",    basedir("/name"));
    expect_str(__LINE__, "",     basedir("name"));
    expect_str(__LINE__, "",     basedir(""));
}

static void test_filename() {
    expect_str(__LINE__, "name", filename("dir/name"));
    expect_str(__LINE__, "",     filename("dir/"));
    expect_str(__LINE__, "name", filename("/name"));
    expect_str(__LINE__, "name", filename("name"));
    expect_str(__LINE__, "",     filename(""));
}

void run_file_test() {
    test_basedir();
    //test_filename();
}




