#include <chrono>
#include <iostream>
#include <stdexcept>

#include "cli.h"
#include "menu.h"
#include "order.h"
#include "orders.h"

void cli::usage() {
  std::cout << std::endl
            << "Usage: " << std::endl
            << "To run a test, enter:" << std::endl
            << "./a.out -t" << std::endl
            << "For an interactive run with no arguents:" << std::endl
            << "./a.out " << std::endl
            << std::endl;
}

void cli::main_menu() {
  cls();
  std::cout << std::endl
            << "********************************************" << std::endl
            << "*  Main Menu" << std::endl
            << "********************************************" << std::endl
            << "1. Waiter" << std::endl
            << "2. Bartender" << std::endl
            << "********************************************" << std::endl;
}

void cli::waiter_menu() {
  std::cout << std::endl
            << "********************************************" << std::endl
            << "*  Waiter Menu" << std::endl
            << "********************************************" << std::endl
            << "1. Add product to order" << std::endl
            << "2. Remove products with the same number" << std::endl
            << "3. Remove product by number and comment" << std::endl
            << "4. Clear all products from order" << std::endl
            << "5. Print order" << std::endl
            << "6. Add order to queue" << std::endl
            << "********************************************" << std::endl;
}

void cli::bartender_menu() {
  std::cout << std::endl
            << "********************************************" << std::endl
            << "*  Bartender menu" << std::endl
            << "********************************************" << std::endl
            << "1. Remove next order" << std::endl
            << "2. Remove an order" << std::endl
            << "3. Print next order" << std::endl
            << "4. Print all orders" << std::endl
            << "********************************************" << std::endl;
}

void cli::validate_cin() {
  if (std::cin.fail()) {
    std::cin.clear();
    std::cin.ignore(256, '\n');
  }
}

int cli::get_selection_with_exit(int max) {
  int selection = 0;
  std::cout << std::endl << "Enter selection from 1 to " << max 
            << " (-1 to exit): ";
  std::cin >> selection;

  while (selection < -1 || selection == 0 || selection > max) {
    validate_cin();
    std::cout << "Invalid input!" << std::endl
              << "Please enter a selection between 1 and " << max << ": ";
    std::cin >> selection;
  } // End while
  cls();
  return selection;
}

int cli::get_selection(int max) {
  int selection = 0;
  std::cout << std::endl << "Enter selection from 1 to " << max << ": ";
  std::cin >> selection;

  while (selection <= 0 || selection > max) {
    validate_cin();
    std::cout << "Invalid input!" << std::endl
              << "Please enter a selection between 1 and " << max << ": ";
    std::cin >> selection;
  } // End while
  cls();
  return selection;
}

std::string get_comment() {
  std::string comment;
  std::cin.clear(); // Clean up cin to avoid issues with getline
  std::cin.ignore(256, '\n');
  std::cout << std::endl << "Enter comment: ";
  getline(std::cin, comment);
  return comment;
}

void cli::waiter_handler(Menu *menu, Orders *orders) {
  int selection = 0;
  int waiter = 0;
  int table = 0;

  std::cout << std::endl
            << "--------------" << std::endl
            << "Waiter details" << std::endl
            << "--------------" << std::endl;
  std::cout << "Waiter number > ";
  waiter = get_selection(3);
  std::cout << "Table number > ";
  table = get_selection(20);

  Order order(waiter, table);

  while (selection != -1) {
    waiter_menu();
    selection = get_selection_with_exit(5);

    switch (selection) {
    case 1: { // Add product from the order
      menu->print();
      int product = get_selection(menu->size());
      std::string comment = get_comment();
      if (order.add(product, comment, menu) == false) {
        std::cout << std::endl
                  << ">>>" << std::endl
                  << "-- Sorry, " << menu->key_from_num(product)
                  << " is out of stock" << std::endl;
      }
      order.print();
      break;
    }
    case 2: { // Remove products from the order that have the same key
      order.print();
      int product = get_selection(menu->size());
      order.remove(product);
      break;
    }
    case 3: { // Remove product from the order by key and comment
      order.print();
      int product = get_selection(menu->size());
      std::string comment = get_comment();
      order.remove(product, comment);
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
        std::cout << std::endl
                  << ">>>" << std::endl
                  << "++ Sorry, cannot add an empty order to the orders queue"
                  << std::endl;
      }
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

  while (selection != -1) {
    bartender_menu();
    selection = get_selection_with_exit(4);

    switch (selection) {
    case 1: { // Remove next order from the orders queue
      if (orders->size() > 0) {
        orders->remove_next();
      } else {
        std::cout << std::endl << "+ All orders are processed." << std::endl;
      } // End if
      break;
    }
    case 2: { // Remove an order from the orders queue
      if (orders->size() > 0) {
        int order_id;
        orders->print_all();
        std::cout << "Enter order id to remove: ";
        std::cin >> order_id;
        try {
          Order order_to_remove = orders->find(order_id);
          orders->remove(order_to_remove);
        } catch (const std::exception &e) {
          std::cout << e.what() << std::endl;
        } // End try/catch
      } else {
        std::cout << std::endl << "+ All orders are processed." << std::endl;
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

void cli::live() {
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

/**
 * cls
 *
 * Clears the screen for clarity of the menu system. Interesting approach!!!
 * found at: https://stackoverflow.com/questions/17335816/clear-screen-using-c
 */
void cli::cls() { std::cout << "\033[2J\033[1;1H"; }