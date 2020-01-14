#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

#include "menu.h"

Menu::Menu() {
  unlimited_ = -1;

  std::string path = "../data/catalog.txt";
  std::string delimeter = "*";
  std::ifstream fd;
  std::string key;
  std::string tmp;
  int value;

	fd.open(path);
  if (fd.fail()) {
    std::cerr << "Error: Cannot open data/catalog.txt" << std::endl;
    exit(1);
  }

  // For each line in the catalog
  while(!fd.eof()) {
    std::string line;
    std::getline(fd, line);
    std::istringstream stream(line);     
    
    // Reset variables
    tmp = ""; 
    key = "";

    // Parse each line
    while (!stream.eof()) {
      stream >> tmp;

      // Exract key
      if (tmp != delimeter) {
        key.append(" ");
        key.append(tmp);
      }

      // Extract value
      if (tmp == delimeter) {
        // If there is no value, the resource is unlimited
        tmp = std::to_string(unlimited_);

        // Otherwise set it to the specified value in the text file
        stream >> tmp;
        value = std::atoi(tmp.c_str());
      }
    }

    // Assign the key and value to the menu catalog
    key = Menu::trim(key, ' ');
    catalog_.emplace(key, value);
  }
	fd.close();
}

void Menu::manage_resource(std::string key) {

  // TODO: Protect operation with a mutex to avoid race conditions
  // TODO: Update catalog text file or not???
  
  for (auto it = catalog_.begin(); it != catalog_.end(); ++it) {
    if ((*it).first == key) {
      if ((*it).second > 0) {
        --(*it).second;
      } // End inner if
    } // End outer if
  } // End for
}

bool Menu::is_available(std::string key) {
  for (auto it = catalog_.begin(); it != catalog_.end(); ++it) {
    if ((*it).first == key) {
      if ((*it).second != 0) {
        return true;
      } // End inner if
    } // End outer if
  } // End for
  return false;
}

std::string Menu::key_from_num(int product) {
  int i = 0;
  std::map<std::string, int>::iterator it;
  for (it = catalog_.begin(); it != catalog_.end(); ++it) {
    // Map iterator start from zero and products displayed on menu start from 1
    if (i == (product - 1)) {
      break;
    }
    ++i;
  }
  return (*it).first; // TODO: If a product is not found we return the last
}

void Menu::print() {
  std::cout << std::endl << "* Coffee shop menu (" << catalog_.size() 
            << ") products" << std::endl;
  
  int i = 1;
  for (auto it = catalog_.begin(); it != catalog_.end(); ++it) {
    std::cout << "  " << i << ". " << (*it).first;
    if ((*it).second > 0) {
      std::cout << " * " << (*it).second;
    }
    ++i;
    std::cout << std::endl;
  }
}

/**
 * trim
 * 
 * A helper method to discard leading and trailing whitespace from string
 */
std::string Menu::trim(std::string& str, char delim) {
  size_t first = str.find_first_not_of(delim);
  size_t last = str.find_last_not_of(delim);
  return str.substr(first, (last - first + 1));
}