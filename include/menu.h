#ifndef MENU_H
#define MENU_H

#include <map>
#include <mutex>
#include <string>

class Menu {
public:
  // Constructor
  Menu();
  
  // Behavior
  void manage_resource(std::string);
  bool is_available(std::string) const;
  std::string key_from_num(int);
  
  // Printing
  void print() const;

private:
  // Helpers
  std::string trim(std::string&, char);

  std::map<std::string, int> catalog_; // Menu catalog with product quantities
  int unlimited_; // Marks products that have unlimited quantities
  std::mutex mtx_; // Controls access to the product consumption
};

#endif /* MENU_H */