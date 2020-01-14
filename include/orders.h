#ifndef ORDERS_H
#define ORDERS_H

#include <deque>
#include <string>

#include "order.h"

class Orders {
public:
  Orders();

  void add(Order);
  void remove_next();
  void remove(Order);
  int size();
  
  void print_next();
  void print_all();

private:
  int coffeshop_id_; // Provision for future versions
  std::deque<Order> orders_;
};

#endif /* ORDERS_H */