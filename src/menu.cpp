#include <fstream>
#include <iostream>
#include <map>
#include <mutex>
#include <sstream>

#include "menu.h"

Menu::Menu(std::string filename) noexcept {
  unlimited_ = -1; // Initialize private member

  std::string path = "../data/" + filename;
  std::string delimeter = "*";
  std::ifstream fd;
  std::string tmp;
  std::string key;
  int value;

  fd.open(path);
  if (fd.fail()) {
    std::cerr << "Error: Cannot open " << path
              << ", please check the file exists." << std::endl;
    exit(1);
  }

  // Initialize the catalog_ private member from the file contents
  while (!fd.eof()) {
    std::string line;
    std::getline(fd, line);
    std::istringstream stream(line);
    tmp = "";
    key = "";

    while (!stream.eof()) {
      stream >> tmp;

      // Exract the key
      if (tmp != delimeter) {
        key.append(" ");
        key.append(tmp);
      } // End if

      // Extract the value
      if (tmp == delimeter) {
        // If there is no value, the resource is considered to be unlimited
        tmp = std::to_string(unlimited_);

        // Otherwise set it to the specified value in the text file
        stream >> tmp;
        value = std::atoi(tmp.c_str());
      } // End if
    }   // End inner while

    // Assign the key and value to the menu catalog
    key = Menu::trim(key, ' ');
    catalog_.emplace(key, value);
  } // End outer while
  fd.close();
}

/**
 * manage_resource
 *
 * - Keeps track of a product that is offered in a limited quantity as set in
 *   the text file
 * - It does NOT update the quantity on the catalog text file
 * - It is an atomic operation to avoid data races in a networked environment as
 * a provision for future versions
 */
void Menu::manage_resource(std::string key) noexcept {
  mtx_.lock();
  for (auto it = catalog_.begin(); it != catalog_.end(); ++it) {
    if ((*it).first == key) {
      if ((*it).second > 0) {
        --(*it).second;
      } // End inner if
    }   // End outer if
  }     // End for
  mtx_.unlock();
}

bool Menu::is_available(std::string key) const noexcept {
  for (auto it = catalog_.begin(); it != catalog_.end(); ++it) {
    if ((*it).first == key) {
      if ((*it).second != 0) { // Remember, -1 is unlimited quantity
        return true;
      } // End inner if
    }   // End outer if
  }     // End for
  return false;
}

std::string Menu::key_from_num(int product) noexcept {
  int i = 0;
  std::map<std::string, int>::iterator it;
  for (it = catalog_.begin(); it != catalog_.end(); ++it) {
    // Map iterator start from zero and products displayed on menu start from 1
    if (i == (product - 1)) {
      break;
    } // End if
    ++i;
  }                   // End for
  return (*it).first; // TODO: If a product is not found we return the last
}

int Menu::size() const noexcept { return catalog_.size(); }

void Menu::print() const noexcept {
  std::cout << std::endl
            << "********************************************" << std::endl
            << "*  Geeks cafe menu (" << size() << ") products" << std::endl
            << "********************************************" << std::endl;
  int catalog_number = 1;
  for (auto it = catalog_.begin(); it != catalog_.end(); ++it) {
    std::cout << "*  " << catalog_number << ". " << (*it).first;
    if ((*it).second >= 0) {
      std::cout << " * " << (*it).second;
    } // End if
    ++catalog_number;
    std::cout << std::endl;
  } // End for
  std::cout << "********************************************" << std::endl;
}

/**
 * trim
 *
 * A helper method to discard leading and trailing whitespace from string
 */
std::string Menu::trim(std::string &str, char delim) noexcept {
  size_t first = str.find_first_not_of(delim);
  size_t last = str.find_last_not_of(delim);
  return str.substr(first, (last - first + 1));
}