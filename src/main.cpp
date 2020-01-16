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
    } // End inner if
  } else {
    cli::handler();
  } // End outer if
  return 0;
}