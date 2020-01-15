#ifndef CLI_H
#define CLI_H

#include "menu.h"
#include "orders.h"

namespace cli {
void main_menu();
void waiter_menu();
void validate_cin();
int get_selection(int);
int get_selection_with_exit(int);
void bartender_menu();
void waiter_handler(Menu *, Orders *);
void bartender_handler(Menu *, Orders *);
void usage();
void live();
void cls();
} // namespace cli

#endif /* CLI_H */