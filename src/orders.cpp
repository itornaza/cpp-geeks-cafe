#include <deque>
#include <iostream>
#include <stdexcept>

#include "order.h"
#include "orders.h"

Orders::Orders() { coffeshop_id_ = 0; }

void Orders::add(Order order) { orders_.push_back(order); }

void Orders::remove_next() {
  if (size() > 0) {
    orders_.pop_front();
  } // End if
}

/**
 * find
 *
 * Finds an order provided the order id. If the order id does not exist it
 * throws an exception.
 */
Order Orders::find(int order_id) {
  if (size() > 0) {
    for (auto it = orders_.begin(); it != orders_.end(); ++it) {
      if (order_id == (*it).get_id()) {
        return *it;
      } // End inner if
    }   // End for    
  } else {
    throw std::runtime_error("+ Exception: The orders queue is empty.");  
  } // End outer if
  throw std::runtime_error("+ Exception: Order does not exist.");
}

void Orders::remove(Order order) {
  if (size() > 0) {
    for (auto it = orders_.begin(); it != orders_.end(); ++it) {
      if (order == *it) {
        orders_.erase(it);
        return; // Otherwise the iterator does not exist anymore
      }         // End inner if
    }           // End for
  }             // End outer if
}

int Orders::size() const { return orders_.size(); }

void Orders::print_next() const {
  if (size() > 0) {
    orders_.front().print();
  } else {
    std::cout << std::endl << "+ All orders are processed." << std::endl;
  } // End if
}

void Orders::print_all() const {
  if (size() > 0) {
    std::cout << std::endl
              << ">>>" << std::endl
              << "+ Pending orders: " << size() << std::endl;
    for (auto it = orders_.begin(); it != orders_.end(); ++it) {
      (*it).print();
    } // End for
  } else {
    std::cout << std::endl << "+ All orders are processed." << std::endl;
  } // End if
}