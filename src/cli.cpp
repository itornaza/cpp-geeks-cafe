#include <chrono>
#include <iostream>
#include <thread>

#include "cli.h"
#include "menu.h"
#include "order.h"
#include "orders.h"

void cli::usage() {
  std::cout << std::endl << "Usage: " << std::endl
            << "To run a simulation, enter:"<< std::endl
            << "./a.out -s" << std::endl
            << "For an interactive run with no arguents:" << std::endl
            << "./a.out " << std::endl << std::endl;
}

void cli::simulation() {
  std::cout << std::endl << "*  Coffee shop simulation" << std::endl;
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

void cli::main_menu() {
  std::cout << "****************************************" << std::endl
            << "*  Main Menu" << std::endl
            << "****************************************" << std::endl
            << "1. Waiter" << std::endl
            << "2. Bartender" << std::endl
            << "****************************************" << std::endl;
}

void cli::waiter_menu() {
  std::cout << "****************************************" << std::endl
            << "*  Waiter Menu" << std::endl
            << "****************************************" << std::endl
            << "1. Add order" << std::endl
            <<" 2. Add product" << std::endl
            << "3. Remove product" << std::endl
            << "4. Clear an order" << std::endl
            << "5. Print order" << std::endl
            << "6. Print menu" << std::endl;
            << "****************************************" << std::endl;
}

void cli::bartender_menu() {
  std::cout << "****************************************" << std::endl
            << "*  Bartender menu" << std::endl
            << "****************************************" << std::endl
            << "1. Remove next order" << std::endl
            << "2. Remove an order" << std::endl
            << "3. Print next order" << std::endl
            << "4. Print all orders" << std::endl
            << "****************************************" << std::endl;
}

void cli::live() {
  Menu menu;
  int waiter = 0;
  int table = 0;
  int product = 0;
  std::string comment;
  
  while (waiter != -1) {
    std::cout << "Enter waiter numnber: ";
    std::cin >> waiter;
    std::cout << "Enter table numnber: ";
    std::cin >> table;

    menu.print();

    Order order(waiter, table);
    while (product != -1) {
      std::cout << "Enter product: ";
      std::cin >> product;
      std::cout << "Enter comment: ";
      std::cin >> comment;
      order.add(product, comment, &menu);
    }
  }
}