#include <assert.h>
#include <iostream>
#include <thread>

#include "menu.h"
#include "order.h"
#include "orders.h"
#include "test.h"

void tst::test() {
  std::cout << std::endl << "* Geeks cafe tests" << std::endl;

  // Set up the objects
  Menu menu("test_catalog.txt");
  Orders orders;

  // Run the test cases
  test_order(&menu, &orders);
  test_orders(&menu, &orders);
  test_menu(&menu, &orders);

  std::cout << "* All tests passed!" << std::endl << std::endl;
}

void tst::test_order(Menu *menu, Orders *orders) {
  std::cout << "+ testing order... ";

  // Test that for the same waiter and with 1 second difference the orders have
  // a different id
  Order order_1(1, 10);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  Order order_2(1, 12);
  assert(order_1.get_id() != order_2.get_id());

  // Test waiter and table numbers
  assert(order_1.get_waiter_id() == 1);
  assert(order_1.get_table_id() == 10);

  // Test that the orders are empty
  assert(order_1.empty() == true);
  assert(order_2.empty() == true);

  // Add some products
  order_1.add(4, "no sugar", menu);
  order_1.add(4, "with a lot of sugar", menu);
  order_1.add(4, "with little sugar", menu);
  order_1.add(3, "one brown suggar", menu);
  order_1.add(1, "flat", menu);

  order_2.add(1, "flat", menu);

  // Test order size
  assert(order_1.size() == 5);

  // Test remove order that has multiple occurencies of the same key
  order_1.remove(4, "no sugar");
  assert(order_1.size() == 4);

  // Test that the orders are not empty
  assert(order_1.empty() == false);
  assert(order_2.empty() == false);

  // Test remove by key
  order_2.remove(1);
  assert(order_2.empty() == true);

  // Test clear
  order_1.clear();
  assert(order_2.empty() == true);

  std::cout << " [ok]" << std::endl;
}

void tst::test_orders(Menu *menu, Orders *orders) {
  std::cout << "+ testing orders... ";

  Order order_1(1, 10);
  std::this_thread::sleep_for(std::chrono::seconds(1));
  Order order_2(2, 12);

  // Cannot add an empty order to the queue
  assert(orders->add(order_1) == false);
  assert(orders->add(order_2) == false);

  // Add products and add the orders to the queue
  order_1.add(4, "no sugar", menu);
  order_2.add(4, "with sugar", menu);
  assert(orders->add(order_1) == true);
  assert(orders->add(order_2) == true);

  // Test orders are two
  assert(orders->size() == 2);

  // Test remove next
  orders->remove();
  assert(orders->size() == 1);

  // Test remove order does not crash on random number
  try {
    Order order = orders->find(23551111);
  } catch (const std::exception &e) {
    std::cout << "(" << e.what() << ")";
  } // End try/catch

  // Test orders are empty
  orders->remove();
  assert(orders->size() == 0);

  // Test cannot remove order from an empty queue
  orders->remove();
  assert(orders->size() == 0);

  std::cout << " [ok]" << std::endl;
}

void tst::test_menu(Menu *menu, Orders *orders) {
  std::cout << "+ testing menu... ";
  Order order_1(3, 3);

  // Test exhaustion of a product that is with limited quanrtities
  // Creme brulee is the second product in the menu with 2 pieces available
  std::string key = menu->key_from_num(2);

  // Get the first two pieces
  for (int i = 2; i > 0; --i) {
    assert(menu->is_available(key) == true);
    order_1.add(2, "with an extra spoon", menu);
  } // End for

  // Try to get one more
  assert(menu->is_available(key) == false);
  assert(order_1.add(2, "with an extra spoon", menu) == false);

  std::cout << " [ok]" << std::endl;
}