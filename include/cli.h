#ifndef CLI_H
#define CLI_H

#include "menu.h"
#include "orders.h"

namespace cli {
// Print
void usage();
void main_menu();
void waiter_menu();
void bartender_menu();
void cls();

// User input
int get_selection(int);
int get_selection_with_exit(int);
int get_int();
std::string get_comment();

// Handlers
void waiter_handler(Menu *, Orders *);
void bartender_handler(Menu *, Orders *);
void handler();
} // namespace cli

#endif /* CLI_H */