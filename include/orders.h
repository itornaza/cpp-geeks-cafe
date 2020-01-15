#ifndef ORDERS_H
#define ORDERS_H

#include <deque>
#include <string>

#include "order.h"

class Orders {
public:
  // Constructor
  Orders();

  // Behavior
  void add(Order);
  Order find(int);  // throws runtime exception
  void remove_next();
  void remove(Order);
  int size() const;

  // Printing
  void print_next() const;
  void print_all() const;

private:
  int coffeshop_id_;         // Provision for future versions
  std::deque<Order> orders_; // FIFO to control the bartender workflow
};

#endif /* ORDERS_H */