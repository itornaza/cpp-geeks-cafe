#include <ctime>
#include <iostream>
#include <map>

#include "menu.h"
#include "order.h"

Order::Order(int waiter_id, int table_id)
    : waiter_id_(waiter_id), table_id_(table_id) {
  Order::set_id(waiter_id);
}

int Order::get_id() const { return id_; }

/**
 * set_id
 *
 * Generates a unique id for this order by combining the waiter id and the
 * number of seconds that has elapsed since the previous midnight.
 */
void Order::set_id(int waiter_id) {
  waiter_id *= 100000;
  int seconds_since_midnight = 0;

  time_t t_now;
  std::time(&t_now);

  tm *date = std::localtime(&t_now);
  date->tm_hour = 0;
  date->tm_min = 0;
  date->tm_sec = 0;

  seconds_since_midnight = difftime(t_now, std::mktime(date));
  id_ = waiter_id + seconds_since_midnight;
}

int Order::get_waiter_id() const { return waiter_id_; }

int Order::get_table_id() const { return table_id_; }

void Order::add(int product, std::string comment, Menu *menu) {
  // Get the catalog key of the product
  std::string key = menu->key_from_num(product);

  // Check if the product is available and try to get it!!!
  if (menu->is_available(key)) {
    products_.insert(std::pair<int, std::string>(product, comment));
    menu->manage_resource(key);
  } else {
    std::cerr << std::endl
              << "-- Sorry, " << key << " is out of stock" << std::endl;
  }
}

void Order::remove(int product) {
  products_.erase(product); // TODO: Erases all products with this key
}

void Order::clear() { products_.clear(); }

int Order::size() const { return products_.size(); }

void Order::print() const {
  std::cout << std::endl
            << ">>>" << std::endl
            << "- Order " << id_ << " from waiter " << waiter_id_
            << " at table " << table_id_ << std::endl;

  if (size() > 0) {
    for (auto it = products_.begin(); it != products_.end(); ++it) {
      std::cout << "-- " << (*it).first << " - " << (*it).second << std::endl;
    }
  } else {
    std::cout << "-- The order is still empty" << std::endl;
  }
}

bool Order::operator==(Order order) { return (id_ == order.id_); }