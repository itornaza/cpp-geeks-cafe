# Geeks Cafe

This project implements a basic coffe shop ordering system where waiters put orders and bartenders handle them in a 'first in first out - FIFO' manner for our geeks, or 'first come first served' for the non-geek customers. Access to this basic functionality is provided through a command line interface to keep dependencies to a bare minimum and provide a base for future gui implementations. Nonetheless, this project highlights above all things the need for coffee as an indespensable companion to writing code.

It is the capstone, or just the last project out of a series of 5 projects that are required for the completion of the C++ Nanodegree from Udacity. It implements 'Capstone Option 1: build the project of your choice' and is compared against this [rubric](https://review.udacity.com/#!/rubrics/2533/view).

Future versions may include client/server architecture with support of multiple clients, ios implementation for the client part, and a desktop gui for the server.

## Expected behavior

The program guides the user through a series of command line menus. Initially it presents the option for selecting between different roles within the coffee shop, i.e. waiter or bartender. The user can have any role without access control being enforced.

If a waiter is selected, a number for the table and another one for the waiter has to be provided by the user. Then a menu of waiter options is presented so the waiter can add, remove or clear all products from the current order. She can also print an order and finally add the order to the queue for handling by the bartender. There is no provision for editing an order after it is pushed to the queue. Orders are supposed to be kind of short and they can just be deleted and filled up again.

If the bartender role is selected, the user can use various printing modes to be able to process the orders. She can also remove orders as they are being ready, or delete any order in case the customer changed her mind. However, the orders arrive and are presented in a FIFO manner so all customers are happy!

Keep in mind that order numbers are in XYYYYY format, where X is the waiter number and YYYYY is the second of the current day ranging from 1 to 86400. This satisfies both the uniqueness of the order as well as a secondary means to distinguish between orders precedence.

## Code structure

```
.
├── CMakeLists.txt
├── README.md
├── data
│   ├── catalog.txt       // The menu catalog in text format, can be set up by the manager
│   └── test_catalog.txt  // The menu catalog in text format, used for unit testing (do not change)
├── include
│   ├── cli.h             // namespace cli
│   ├── menu.h            // class Menu
│   ├── order.h           // class Order
│   ├── orders.h          // class Orders
│   └── test.h            // namespace tst
└── src
    ├── cli.cpp           // Command line interface implementation
    ├── client.cpp        // Future provision
    ├── main.cpp          // Command line options
    ├── menu.cpp          // class Menu
    ├── order.cpp         // class Order
    ├── orders.cpp        // class Orders
    ├── server.cpp        // Future provision
    └── test.cpp          // Tests implementation
```

## Implementation notes

The menu catalog is provided through a text file that can be found at `/data/catalog.txt`. The file is parsed from the program to provide a starting point for daily coffee shop operations. The manager can edit this file as she sees fit as a preliminary act before launching the program. The file `/data/test_catalog.txt` is intended for unit testing it used by test.cpp and shall not be changed or it willl affect the test behavior.

The backbone of the program is consisted of three classes, namely `class Menu`, `class Orders`, `class Order`. Lets have a look at them in more detail.

* `Menu` handles the initialization of the menu catalog from the `/datacatalog.txt` file. It also provides a simple resource management system to keep track of products that are limited in number at the coffee shop inventory. For example there might be only 5 Creme brulees and the FIFO concept must be stricktly applied. The rest is basic functionality to print and access menu items.

* `Orders` provides the FIFO mechanism to handle individual orders appropriatelly. It provides features to add, access, remove orders from the orders queue, as well as printing functionality.

* `Order` is the class that handles the individual orders to support our waiters. We need a unique id for each order and we create it by combining the waiter's id with the second of the day that the order is taken. Within the order we find a multimap object that keeps track of the product that was ordered associated with an optional comment from the customer, like "one brown sugar and no cream". Of course basic functionality to add remove and clear products from our order is included as well.

The command line interface is implemented in a separate file named `cli.cpp` so it can be easily replaced by a more sophisticated gui. The respective functions are packed together in `namespace cli` for code clarity.

Following the same style, tests are implemented in `test.cpp` and can be launched with the `-t` option, as described below in the 'Basic build instructions' section.

## Rubric points addressed

### Loops, Funtions, I/O
1. The project demonstrates an understanding of C++ functions and control structures.
    * In the file `/src/cli.cpp`, the `waiter_handler()` function at lines TODO demonstrates if, while and switch control structures. In addition, this file organises functions under the namespace `cli`.
2. The project reads data from a file and process the data, or the program writes data to a file.
    * In the file `/src/menu.cpp`, the constructor of the `class Menu` at line TODO accepts a filename as an argument and uses it to access the file located at `/data/catalog.txt` to initialize the `catalog_` private member of the class.
3. The project accepts user input and processes the input.
    * In the `src/cli.cpp` file there are 4 functions that accept, validate and handle user input. Namely: validate_cin(), get_selection_with_exit() get_selection() and get_comment().

### Object Oriented Progeamming
1. The project uses Object Oriented Programming techniques.
    * There are 3 classes in the project. `Order`, `Orders` and `Menu` that are respecively found in the `order.cpp`, `orders.cpp` and `menu.cpp`.
2. Classes use appropriate access specifiers for class members.
    * In class `Menu`, there are public and private mebers.
7. Overloaded functions allow the same function to operate on different parameters.
    * In class `Order` there are two member functions named `remove` that are overloaded with different arguments. 

## Dependencies for running locally
* cmake >= 3.11
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic build instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./cafe`
5. Usage: `./cafe -h`
6. Tests: `./cafe -t`
