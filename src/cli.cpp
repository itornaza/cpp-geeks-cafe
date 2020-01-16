#include <chrono>
#include <iostream>
#include <stdexcept>

#include "cli.h"
#include "menu.h"
#include "order.h"
#include "orders.h"

//---------------------
// Display 
//---------------------

void cli::usage() {
  cls();
  std::cout << std::endl
    << "********************************************" << std::endl
    << "*    Geeks cafe usage:                      " << std::endl
    << "********************************************" << std::endl
    << "* 1. To run the program, enter:             " << std::endl
    << "* $ ./cafe                                  " << std::endl 
    << "*                                           " << std::endl
    << "* 2. To run the test suite, enter:          " << std::endl
    << "* $ ./cafe -t                               " << std::endl 
    << "*                                           " << std::endl
    << "* 3. To show how to use, enter:             " << std::endl
    << "* $ ./cafe -h                               " << std::endl
    << "********************************************" << std::endl;
}

void cli::main_menu() {
  cls();
  std::cout << std::endl
    << "********************************************" << std::endl
    << "*    Main Menu                              " << std::endl
    << "********************************************" << std::endl
    << "* 1. Waiter                                 " << std::endl
    << "* 2. Bartender                              " << std::endl
    << "********************************************" << std::endl;
}

void cli::waiter_menu() {
  std::cout << std::endl
    << "********************************************" << std::endl
    << "*    Waiter Menu                            " << std::endl
    << "********************************************" << std::endl
    << "* 1. Add product to order                   " << std::endl
    << "* 2. Remove products with the same number   " << std::endl
    << "* 3. Remove product by number and comment   " << std::endl
    << "* 4. Clear all products from order          " << std::endl
    << "* 5. Print order                            " << std::endl
    << "* 6. Add order to queue                     " << std::endl
    << "********************************************" << std::endl;
}

void cli::bartender_menu() {
  std::cout << std::endl
    << "********************************************" << std::endl
    << "*    Bartender menu                         " << std::endl
    << "********************************************" << std::endl
    << "* 1. Remove next order                      " << std::endl
    << "* 2. Remove an order                        " << std::endl
    << "* 3. Print next order                       " << std::endl
    << "* 4. Print all orders                       " << std::endl
    << "********************************************" << std::endl;
}

/**
 * cls
 *
 * Clears the screen for clarity of the menu system. Interesting approach!!!
 * found at: https://stackoverflow.com/questions/17335816/clear-screen-using-c
 */
void cli::cls() { std::cout << "\033[2J\033[1;1H"; }

//---------------------
// User input
//---------------------

int cli::get_selection_with_exit(int max) {
  std::cout << std::endl << "Enter selection from 1 to " << max 
    << " (-1 to exit): ";
  int selection = get_int();
  while (selection < -1 || selection == 0 || selection > max) {
    std::cout << std::endl << ">>>" << std::endl
      << "Invalid input!" << std::endl
      << "Please enter a selection between 1 and " << max << ": ";
    selection = get_int();
  } // End while
  return selection;
}

int cli::get_selection(int max) {
  std::cout << std::endl << "Enter selection from 1 to " << max << ": ";
  int selection = get_int();
  while (selection <= 0 || selection > max) {
    std::cout << std::endl << ">>>" << std::endl
      << "Invalid input!" << std::endl
      << "Please enter a selection between 1 and " << max << ": ";
    selection = get_int();
  } // End while
  return selection;
}

int cli::get_int() {
  int selection = 0;
  std::cin >> selection;
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(256, '\n');
  } // End if
  return selection;
}

std::string cli::get_comment() {
  std::string comment;
  std::cin.clear();
  std::cin.ignore(256, '\n');
  std::cout << std::endl << "Enter comment: ";
  getline(std::cin, comment);
  return comment;
}

//---------------------
// Handlers
//---------------------

void cli::waiter_handler(Menu *menu, Orders *orders) {
  int selection = 0;
  int waiter = 0;
  int table = 0;
  
  cls();
  std::cout << std::endl
    << "--------------" << std::endl
    << "Waiter details" << std::endl
    << "--------------" << std::endl;
  std::cout << "Waiter number:";
  waiter = get_selection(3);
  std::cout << "Table number:";
  table = get_selection(20);
  cls();

  Order order(waiter, table);

  while (selection != -1) {
    waiter_menu();
    selection = get_selection_with_exit(6);
    cls();
    switch (selection) {
    case 1: { // Add product to order
      menu->print();
      int product = get_selection(menu->size());
      std::string comment = get_comment();
      cls();
      if (order.add(product, comment, menu) == false) {
        std::cout << std::endl << ">>>" << std::endl
          << "-- Sorry, " << menu->key_from_num(product)
          << " is out of stock" << std::endl;
      } // End if
      order.print();
      break;
    }
    case 2: { // Remove products from the order that have the same key
      order.print();
      if (order.empty() == false) {
        int product = get_selection(menu->size());
        cls();
        order.remove(product);
      } // End if
      break;
    }
    case 3: { // Remove product from the order by key and comment
      order.print();
      if (order.empty() == false) {
        int product = get_selection(menu->size());
        std::string comment = get_comment();
        cls();
        order.remove(product, comment);
      } // End if
      break;
    }
    case 4: { // Clear all products from the order
      order.clear();
      break;
    }
    case 5: { // Print order
      order.print();
      break;
    }
    case 6: { // Add order to the orders queue
      // When the order is added to the orders queue, we are closing this order
      // and return to the main menu.
      if (orders->add(order)) {
        selection = -1;
      } else {
        std::cout << std::endl << ">>>" << std::endl
          << "++ Sorry, cannot add an empty order to the orders queue"
          << std::endl;
      } // End if/else
      break;
    }
    default: { // Need an escape route!!!
      selection = -1;
      break;
    } // End default
    } // End switch
  }   // End while
}

void cli::bartender_handler(Menu *menu, Orders *orders) {
  int selection = 0;
  cls();
  while (selection != -1) {
    bartender_menu();
    selection = get_selection_with_exit(4);
    cls();

    switch (selection) {
    case 1: { // Remove next order from the orders queue
      if (orders->size() > 0) {
        orders->remove();
      } else {
        std::cout << std::endl << ">>>" << std::endl
          << "+ All orders are processed" << std::endl;
      } // End if
      break;
    }
    case 2: { // Remove an order from the orders queue
      if (orders->size() > 0) {
        orders->print_all();
        std::cout << std::endl << "Enter order id to remove: ";
        int order_id = get_int();
        try {
          Order order_to_remove = orders->find(order_id);
          orders->remove(order_to_remove);
        } catch (const std::exception &e) {
          std::cout << e.what() << std::endl;
        } // End try/catch
      } else {
        std::cout << std::endl << ">>>" << std::endl
          << "+ All orders are processed" << std::endl;
      } // End if
      break;
    }
    case 3: { // Print next order in the orders queue
      orders->print_next();
      break;
    }
    case 4: { // Print all orders in the orders queue
      orders->print_all();
      break;
    }
    default: { // Need an escape route!!!
      selection = -1;
      break;
    } // End default
    } // End switch
  }   // End while
}

void cli::handler() {
  Menu menu("catalog.txt");
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
    } // End if
  }   // End while
}
