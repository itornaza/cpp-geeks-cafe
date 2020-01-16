#include <deque>
#include <iostream>
#include <stdexcept>

#include "order.h"
#include "orders.h"

Orders::Orders() noexcept { coffeshop_id_ = 0; }

/**
 *  add
 *
 *  Adds a non empty order to the orders queue
 */
bool Orders::add(Order order) noexcept {
  bool is_added = false;
  if (order.empty() == false) {
    orders_.push_back(order);
    is_added = true;
  } // End if
  return is_added;
}

void Orders::remove() noexcept {
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
  throw std::runtime_error("+ Exception: This order does not exist.");
}

void Orders::remove(Order order) noexcept {
  if (size() > 0) {
    for (auto it = orders_.begin(); it != orders_.end(); ++it) {
      if (order == *it) {
        orders_.erase(it);
        return; // Otherwise the iterator does not exist anymore
      }         // End inner if
    }           // End for
  }             // End outer if
}

int Orders::size() const noexcept { return orders_.size(); }

void Orders::print_next() const noexcept {
  if (size() > 0) {
    orders_.front().print();
  } else {
    std::cout << std::endl << ">>>" << std::endl
      << "+ All orders are processed! Keep up the good work!" 
      << std::endl;
  } // End if
}

void Orders::print_all() const noexcept {
  if (size() > 0) {
    std::cout << std::endl << ">>>" << std::endl
      << "+ Pending orders: " << size() << std::endl;
    for (auto it = orders_.begin(); it != orders_.end(); ++it) {
      (*it).print();
    } // End for
  } else {
    std::cout << std::endl << ">>>" << std::endl
      << "+ All orders are processed! Good job, ask for a raise!" 
      << std::endl;
  } // End if
}