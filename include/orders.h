#ifndef ORDERS_H
#define ORDERS_H

#include <queue>
#include <string>
#include <map>

#include "order.h"

class Orders {
public:
  Orders();
  void add_order(Order);
  void remove_order();

private:
  int coffeshop_id_;
  std::priority_queue<Order> orders_;
};

#endif /* ORDERS_H */