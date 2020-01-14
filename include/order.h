#ifndef ORDER_H
#define ORDER_H

#include <map>
#include <string>

#include "menu.h"

class Order {
public:
  // Constructor
  Order(int, int);
  
  // Getters and setters
  void set_id(int);
  int get_id() const;
  int get_waiter_id() const;
  int get_table_id() const;
  
  // Behavior
  void add(int, std::string, Menu *);
  void remove(int);
  void clear();
  bool operator==(Order);

  // Printing
  void print() const;

private:
  int id_;
  int table_id_;
  int waiter_id_;
  std::multimap<int, std::string> products_; // Product catalog num and comment
};

#endif /* ORDER_H */