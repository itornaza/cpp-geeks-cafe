#ifndef ORDER_H
#define ORDER_H

#include <map>
#include <string>

#include "menu.h"

class Order {
public:
  // Constructor
  Order(int, int) noexcept;

  // Getters and setters
  void set_id(int) noexcept;
  int get_id() const noexcept;
  int get_waiter_id() const noexcept;
  int get_table_id() const noexcept;

  // Behavior
  bool add(int, std::string, Menu *) noexcept;
  void remove(int) noexcept;
  void clear() noexcept;
  int size() const noexcept;
  bool empty() const noexcept;
  bool operator==(Order) noexcept;

  // Printing
  void print() const noexcept;

private:
  int id_;
  int table_id_;
  int waiter_id_;
  std::multimap<int, std::string> products_; // Product catalog num and comment
};

#endif /* ORDER_H */