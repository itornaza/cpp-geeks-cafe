#include <iostream>

#include "menu.h"
#include "order.h"
#include "orders.h"

int main() {
  
  //----------
  // Menu
  //----------

  Menu menu;
  std::cout << "products in menu: " << menu.catalog_.size() << std::endl;

  //----------
  // Order
  //----------
  
  Order order(1);
  order.add(2, "no sugar");
  order.add(3, "one brown suggar");
  order.print();
  
  //----------
  // Orders
  //----------


  return 0;
}