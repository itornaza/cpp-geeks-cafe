#include <deque>
#include <iostream>
#include <stdexcept>

#include "orders.h"
#include "order.h"

Orders::Orders() { coffeshop_id_ = 0; }

void Orders::add(Order order) { orders_.push_back(order); }

void Orders::remove_next() {
  if (orders_.size() > 0) {
    orders_.pop_front();
  }
}

/**
 * find
 * 
 * Finds an order provided the order id. If the order id does not exist it 
 * throws an exception.
 */
Order Orders::find(int order_id) {
  for (auto it = orders_.begin(); it != orders_.end(); ++it) {
    if (order_id == (*it).get_id()) {
      return *it;
    }
  }
  throw std::runtime_error("Exception: Order id does not exist");
}

void Orders::remove(Order order) {
  if (orders_.size() > 0) {
    for (auto it = orders_.begin(); it != orders_.end(); ++it) {
      if (order == *it) {
        orders_.erase(it);
        return; // Otherwise the iterator does not exist anymore
      } // End inner if
    } // End for
  } // End outer if
}

int Orders::size() const { return orders_.size(); }

void Orders::print_next() const {
  if (orders_.size() > 0) {
    orders_.front().print();
  }
}

void Orders::print_all() const {
  std::cout << std::endl << "+ Pending orders: " << Orders::size() << std::endl;
  for (auto it = orders_.begin(); it != orders_.end(); ++it) {
    (*it).print();
  }
}