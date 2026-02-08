#ifndef TEAMMEMBER_H
#define TEAMMEMBER_H

#include <string>

struct TeamMember {
    int id;
    std::string name;
    std::string role;
    TeamMember* nextSibling;
    TeamMember* firstChild;
    TeamMember* parent;
    
    TeamMember(int id, const std::string& name, const std::string& role);
    void display() const;
};

#endif
