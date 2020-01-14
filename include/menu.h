#ifndef MENU_H
#define MENU_H

#include <map>
#include <string>

class Menu {
public:
  Menu();
  
  void manage_resource(std::string);
  bool is_available(std::string);
  std::string key_from_num(int);
  
  void print();

private:
  std::string trim(std::string&, char);
  std::map<std::string, int> catalog_;
  int unlimited_;
};

#endif /* MENU_H */