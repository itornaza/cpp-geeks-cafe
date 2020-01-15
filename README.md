# Coffee shop ordering system

This project implements a basic coffe shop ordering system where waiters put orders and bartenders handle them in a first in first out (FIFO) manner. Access to this basic functionality is provided through a command line interface to keep dependencies to a bare minimum and provide a base for future gui implementations.

It is the capstone, or just the last project, out of a series of 5 projects that are required for the completion of the C++ Nanodegree from Udacity. Nonetheless, this project highlights above all things the need for coffee as a indespensable companion to writing code.

Future versions shall include a client/server architecture, ios implementation for the client part, and a desktop gui for the server.

## Directiry structure

`/data` contains the catalog in text format
`/include` contains all the respective header files.
`/src` contains all the cpp files.

## Implementation notes

The menu catalog is provided through a text file that can be found at `/data/catalog.txt`. The file is parsed from the program to provide a starting point for daily coffee shop operations. The manager can edit this file as she sees fit as a preliminary act before launching the program.

The backbone of the program is consisted of three classes, namely `class Menu`, `class Orders`, `class Order`. Lets have a look at them in more detail.

* `Menu` handles the initialization of the menu catalog from the `/datacatalog.txt` file. It also provides a simple resource management system to keep track of products that are limited in number at the coffee shop inventory. For example there might be only 5 Creme brulees and the FIFO concept must be stricktly applied. The rest is basic functionality to print and access menu items.

* `Orders` provides the FIFO mechanism to handle individual orders appropriatelly. It provides features to add, access, remove orders from the orders queue, as well as printing functionality.

* `Order` is the class that handles the individual orders to support our waiters. We need a unique id for each order and we create it by combining the waiter's id with the second of the day that the order is taken. Within the order we find a multimap object that keeps track of the product that was ordered associated with an optional comment from the customer, like "one brown sugar and no cream". Of course basic functionality to add remove and clear products from our order is included as well.

The command line interface is implemented in a separate file named `cli.cpp` so it can be easily replaced by a more advanced gui. The respective functions are packed together in `namespace cli` for code clarity.

There are some tests implemented in `test.cpp` which can be launched with the `-t` option.

## Dependencies for Running Locally
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

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./coffee`
5. Usage: `./coffee -h`
6. Tests: `./coffee -t`
