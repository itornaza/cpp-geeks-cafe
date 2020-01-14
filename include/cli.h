#ifndef CLI_H
#define CLI_H

#include "menu.h"
#include "orders.h"

namespace cli {
void usage();
void test();
void live();
void main_menu();
void waiter_menu();
void waiter_handler(Menu *, Orders *);
void bartender_menu();
void bartender_handler(Menu *, Orders *);
int get_selection(int);
int get_selection_with_exit(int);
void cls();
} // namespace cli

#endif /* CLI_H */