#ifndef ORDERS_H
#define ORDERS_H

#include <deque>
#include <string>

#include "order.h"

class Orders {
public:
  // Constructor
  Orders() noexcept;

  // Behavior
  bool add(Order) noexcept;
  Order find(int); // throws runtime exception
  void remove() noexcept;
  void remove(Order) noexcept;
  int size() const noexcept;

  // Printing
  void print_next() const noexcept;
  void print_all() const noexcept;

private:
  int coffeshop_id_;         // Provision for future versions
  std::deque<Order> orders_; // FIFO to control the bartender workflow
};

#endif /* ORDERS_H */