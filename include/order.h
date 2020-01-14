#ifndef ORDER_H
#define ORDER_H

#include <map>
#include <string>

#include "menu.h"

class Order {
public:
  Order(int, int);
  
  void set_id(int);
  int get_id();
  int get_waiter_id();
  int get_table_id();
  
  void add(int, std::string, Menu *);
  void remove(int);
  void clear();
  bool operator==(Order);

  void print();

private:
  int id_;
  int table_id_;
  int waiter_id_;
  std::multimap<int, std::string> products_;
};

#endif /* ORDER_H */