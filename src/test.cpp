#include <iostream>
#include <assert.h> // TODO
#include <thread>

#include "test.h"
#include "menu.h"
#include "order.h"
#include "orders.h"

// TODO: Unit tests v assert
// TODO: Test more cases

void tst::test() {

  std::cout << std::endl << "*  Coffee shop tests" << std::endl;
  Menu menu;
  menu.print();

  // Order
  Order order(1, 10);
  order.add(2, "no sugar", &menu);
  order.add(2, "with a lot of sugar", &menu);
  order.add(2, "with little sugar", &menu);
  order.add(3, "one brown suggar", &menu);
  order.add(1, "flat", &menu);

  std::this_thread::sleep_for(std::chrono::seconds(2));
  Order order_2(2, 12);
  order_2.add(1, "flat", &menu);

  // Orders
  Orders orders;
  orders.add(order);
  orders.add(order_2);
  orders.print_all();
  orders.remove(order_2);
  orders.print_all();

  menu.print();
}