#ifndef ORDER_H
#define ORDER_H

#include <map>
#include <string>

class Order {
public:
  Order(int);
  void set_id(int);
  int get_id();
  void set_waiter_id(int);
  int get_waiter_id();
  void add(int, std::string);
  void remove(int);
  void clear();
  void print();

private:
  int id_;
  int waiter_id_;
  std::multimap<int, std::string> products_;
};

#endif /* ORDER_H */