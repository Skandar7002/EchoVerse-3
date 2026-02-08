#include "teammember.h"
#include <iostream>

TeamMember::TeamMember(int id, const std::string& name, const std::string& role)
    : id(id), name(name), role(role), nextSibling(nullptr), 
      firstChild(nullptr), parent(nullptr) {}

void TeamMember::display() const {
    std::cout << "ID: " << id << ", Name: " << name 
              << ", Role: " << role;
    if (parent) {
        std::cout << ", Parent: " << parent->name;
    }
    std::cout << std::endl;
}
