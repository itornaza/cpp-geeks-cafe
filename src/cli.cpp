#include <chrono>
#include <iostream>
#include <thread>

#include "cli.h"
#include "menu.h"
#include "order.h"
#include "orders.h"


// TODO: Move output from the API to this file

void cli::usage() {
  std::cout << std::endl << "Usage: " << std::endl
            << "To run a test, enter:"<< std::endl
            << "./a.out -t" << std::endl
            << "For an interactive run with no arguents:" << std::endl
            << "./a.out " << std::endl << std::endl;
}

void cli::test() {
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
  cli::cls();
  std::cout << std::endl 
            << "****************************************" << std::endl
            << "*  Main Menu" << std::endl
            << "****************************************" << std::endl
            << "1. Waiter" << std::endl
            << "2. Bartender" << std::endl
            << "****************************************" << std::endl;
}

void cli::waiter_menu() {
  std::cout << std::endl 
            << "****************************************" << std::endl
            << "*  Waiter Menu" << std::endl
            << "****************************************" << std::endl
            << "1. Add product to order" << std::endl
            << "2. Remove product from order" << std::endl
            << "3. Clear all products from order" << std::endl
            << "4. Print order" << std::endl
            << "5. Add order to queue" << std::endl
            << "****************************************" << std::endl;
}

void cli::waiter_handler(Menu *menu, Orders *orders) {
  int selection = 0;
  int waiter = 0;
  int table = 0;

  // Get details from the waiter
  std::cout << std::endl << "Waiter details: " << std::endl;
  std::cout << "Enter waiter number (1-3): ";
  waiter = get_selection(3);
  std::cout << "Enter table number (1-20): ";
  table = get_selection(20);

  // Initialize an order
  Order order(waiter, table);

  while (selection != -1) { 
    waiter_menu();
    selection = get_selection_with_exit(5);
    
    switch(selection) {
      case 1: {
        // Add product
        cli::cls();
        menu->print();
        int product = get_selection(menu->size());
        std::cin.clear();
        std::cin.ignore();
        std::string comment;
        std::cout << "Enter comment: ";
        getline(std::cin, comment); 
        order.add(product, comment, menu);
        order.print();
        break;
      }
      case 2: {
        // Remove product
        cli::cls();
        order.print();
        int product = get_selection(menu->size());
        order.remove(product);
        break;
      }
      case 3: {
        // Clear all products
        cli::cls();
        order.clear();
        break;
      }
      case 4: {
        // Print order
        cli::cls();
        order.print();
        break;
      }
      case 5: {
        // Add order
        cli::cls();
        orders->add(order);
        break;
      }
      case 6: {
        // Print order
        cli::cls();
        order.print();
      }
      case -1: break; // Need an escape route!!!
      default: break;
    } // End switch
  } // End while
}

void cli::bartender_menu() {
  std::cout << std::endl 
            << "****************************************" << std::endl
            << "*  Bartender menu" << std::endl
            << "****************************************" << std::endl
            << "1. Remove next order" << std::endl
            << "2. Remove an order" << std::endl
            << "3. Print next order" << std::endl
            << "4. Print all orders" << std::endl
            << "****************************************" << std::endl;
}

void cli::bartender_handler(Menu *menu, Orders *orders) {
  int selection = 0;
  
  while (selection != -1) { 
    bartender_menu();
    selection = get_selection_with_exit(4);
    
    switch(selection) {
      case 1: {
        // Remove next order
        if (orders->size() > 0) {
          orders->remove_next();
        }
        break;
      }
      case 2: {
        // Remove an order  
        int order_id;
        orders->print_all();
        std::cout << "Enter order id to remove: ";
        std::cin >> order_id;
        orders->remove(order_id);
        break;
      }
      case 3: {
        // Print next order
        orders->print_next();
        break;
      }
      case 4: {
        // Print all orders
        orders->print_all();
        break;
      }
      case -1: break; // Need an escape route!!!
      default: break;
    } // End switch
  } // End while
}

int cli::get_selection_with_exit(int max) {
  int selection = 0;
  std::cout << "Enter selection from 1 to " << max << " (-1 to exit): ";
  std::cin >> selection;
  while (selection < -1 || selection == 0 || selection > max ) {
    std::cout << "Invalid input, please enter a selection between 1 and " 
              << max << ": ";
    std::cin >> selection;
  }
  return selection;
}

int cli::get_selection(int max) {
  int selection = 0;
  std::cout << "Enter selection from 1 to " << max << ": ";
  std::cin >> selection;
  while (selection <= 0 || selection > max ) {
    std::cout << "Invalid input, please enter a selection between 1 and " 
              << max << ": ";
    std::cin >> selection;
  }
  return selection;
}

void cli::live() {
  Menu menu;
  Orders orders;
  int selection = 0;
  
  while (selection != -1) { 
    main_menu();
    selection = get_selection_with_exit(2); 
    if (selection == 1) {
      waiter_handler(&menu, &orders);
    } else if (selection == 2) {
      bartender_handler(&menu, &orders);
    } else {
      selection = -1;
    }
  }
}

// https://stackoverflow.com/questions/17335816/clear-screen-using-c
void cli::cls() {
  std::cout << "\033[2J\033[1;1H"; // Clears the screen
}