#ifndef TEST_H
#define TEST_H

#include "menu.h"
#include "orders.h"

namespace tst {
// Test suite
void test();

// Test cases
void test_order(Menu *, Orders *);
void test_orders(Menu *, Orders *);
void test_menu(Menu *, Orders *);
} // namespace tst

#endif /* TEST_H */