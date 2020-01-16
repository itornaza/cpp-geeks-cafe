#ifndef MENU_H
#define MENU_H

#include <map>
#include <mutex>
#include <string>

class Menu {
public:
  // Constructor
  Menu(std::string) noexcept;

  // Behavior
  void manage_resource(std::string) noexcept;
  bool is_available(std::string) const noexcept;
  std::string key_from_num(int) noexcept;
  int size() const noexcept;

  // Printing
  void print() const noexcept;

private:
  // Helpers
  std::string trim(std::string &, char) noexcept;

  std::map<std::string, int> catalog_; // Menu catalog with product quantities
  int unlimited_;  // Marks products that have unlimited quantities
  std::mutex mtx_; // Controls access to the product consumption
};

#endif /* MENU_H */