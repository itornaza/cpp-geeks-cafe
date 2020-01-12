#ifndef MENU_H
#define MENU_H

#include <map>
#include <string>

class Menu {
public: 
  std::map<int, std::string> catalog_;
  Menu();
};

#endif /* MENU_H */