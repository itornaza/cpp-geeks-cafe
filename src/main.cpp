#include <iostream>
#include <string>

#include "cli.h"
#include "test.h"

int main(int argc, char *argv[]) {
  if (argc > 1) {
    std::string s(argv[1]);
    if (s == "-t") {
      tst::test();
    } else if (s == "-h") {
      cli::usage();
    }
  } else {
    cli::live();
  }
  return 0;
}