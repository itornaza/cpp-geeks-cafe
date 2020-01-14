#include <string>
#include <iostream>

#include "cli.h"

int main(int argc, char *argv[]) {
  if (argc > 1) {
    std::string s(argv[1]);
    if (s == "-s") {
      cli::simulation();
    } else if (s == "-h") {
      cli::usage();
    }
  } else {
    cli::live();
  }

  return 0;
}