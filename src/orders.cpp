#include <deque>
#include <iostream>

#include "orders.h"

Orders::Orders() { coffeshop_id_ = 0; }

void Orders::add(Order order) { orders_.push_back(order); }

void Orders::remove_next() {  
  if (orders_.size() > 0) { 
    orders_.pop_front();
  } 
}

void Orders::remove(int order_id) {
  for (auto it = orders_.begin(); it != orders_.end(); ++it) {
    if (order_id == (*it).get_id()) {
      orders_.erase(it);
      return; // Otherwise the iterator does not exist anymore
    }
  }
}

void Orders::remove(Order order) {
  for (auto it = orders_.begin(); it != orders_.end(); ++it) {
    if (order == *it) {
      orders_.erase(it);
      return; // Otherwise the iterator does not exist anymore
    }
  }
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