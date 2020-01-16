#ifndef CLI_H
#define CLI_H

#include "menu.h"
#include "orders.h"

namespace cli {
void usage();
void main_menu();
void waiter_menu();
void bartender_menu();
void validate_cin();
int get_selection(int);
int get_selection_with_exit(int);
std::string get_comment();
void waiter_handler(Menu *, Orders *);
void bartender_handler(Menu *, Orders *);
void live();
void cls();
} // namespace cli

#endif /* CLI_H */