#include <deque>
#include <iostream>

#include "orders.h"

Orders::Orders() { coffeshop_id_ = 0; }

void Orders::add(Order order) { orders_.push_back(order); }

void Orders::remove_next() { orders_.pop_front(); }

void Orders::remove(Order order) {
  for (auto it = orders_.begin(); it != orders_.end(); ++it) {
    if (order == *it) {
      orders_.erase(it);
      return; // Otherwise the iterator does not exist anymore
    }
  }
}

void Orders::print_next() { orders_.front().print(); }

void Orders::print_all() {
  std::cout << std::endl << "+ Pending orders: " << Orders::size() << std::endl;
  for (auto it = orders_.begin(); it != orders_.end(); ++it) {
    (*it).print();
  }
}

int Orders::size() { return orders_.size(); }
