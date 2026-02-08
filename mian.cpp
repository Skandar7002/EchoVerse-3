#include "hierarchytree.h"
#include <iostream>

void showMenu() {
    std::cout << "\n=== Podcast Production Team Hierarchy ===\n";
    std::cout << "1. Set Root (Team Leader)\n";
    std::cout << "2. Add Team Member\n";
    std::cout << "3. Remove Team Member\n";
    std::cout << "4. Display Team Hierarchy\n";
    std::cout << "5. Search Member (BFS)\n";
    std::cout << "6. Search Member (DFS)\n";
    std::cout << "7. Auto Test\n";
    std::cout << "8. Exit\n";
    std::cout << "Choice: ";
}

void setRoot(HierarchyTree& tree) {
    std::string name, role;
    
    if (!tree.isEmpty()) {
        std::cout << "Root already set!" << std::endl;
        return;
    }
    
    std::cout << "Team Leader Name: ";
    std::cin.ignore();
    std::getline(std::cin, name);
    
    std::cout << "Role: ";
    std::getline(std::cin, role);
    
    tree.setRoot(name, role);
}

void addMember(HierarchyTree& tree) {
    if (tree.isEmpty()) {
        std::cout << "Please set root first!" << std::endl;
        return;
    }
    
    int parentId;
    std::string name, role;
    
    std::cout << "Parent Member ID: ";
    std::cin >> parentId;
    std::cin.ignore();
    
    std::cout << "New Member Name: ";
    std::getline(std::cin, name);
    
    std::cout << "Role: ";
    std::getline(std::cin, role);
    
    tree.addMember(parentId, name, role);
}

void removeMember(HierarchyTree& tree) {
    if (tree.isEmpty()) {
        std::cout << "Tree is empty!" << std::endl;
        return;
    }
    
    int id;
    std::cout << "Member ID to remove: ";
    std::cin >> id;
    
    tree.removeMember(id);
}

void searchBFS(HierarchyTree& tree) {
    if (tree.isEmpty()) {
        std::cout << "Tree is empty!" << std::endl;
        return;
    }
    
    std::string name;
    std::cout << "Enter name to search (BFS): ";
    std::cin.ignore();
    std::getline(std::cin, name);
    
    TeamMember* result = tree.bfsSearch(name);
    if (result) {
        std::cout << "\nMember found with BFS:\n";
        result->display();
    } else {
        std::cout << "Member not found!" << std::endl;
    }
}

void searchDFS(HierarchyTree& tree) {
    if (tree.isEmpty()) {
        std::cout << "Tree is empty!" << std::endl;
        return;
    }
    
    std::string name;
    std::cout << "Enter name to search (DFS): ";
    std::cin.ignore();
    std::getline(std::cin, name);
    
    TeamMember* result = tree.dfsSearch(name);
    if (result) {
        std::cout << "\nMember found with DFS:\n";
        result->display();
    } else {
        std::cout << "Member not found!" << std::endl;
    }
}

void autoTest(HierarchyTree& tree) {
    std::cout << "\n=== Starting Auto Test ===\n";
    
    std::cout << "\n1. Setting root...\n";
    tree.setRoot("Alice Johnson", "Producer");
    
    std::cout << "\n2. Adding team members...\n";
    tree.addMember(1, "Bob Smith", "Audio Engineer");
    tree.addMember(1, "Charlie Brown", "Content Writer");
    tree.addMember(2, "David Wilson", "Sound Designer");
    tree.addMember(2, "Eva Green", "Mixing Engineer");
    tree.addMember(3, "Frank Miller", "Script Writer");
    tree.addMember(3, "Grace Lee", "Researcher");
    tree.addMember(4, "Henry Ford", "Foley Artist");
    
    std::cout << "\n3. Displaying team hierarchy:\n";
    tree.displayTree();
    
    std::cout << "\n4. Searching for 'Grace Lee' with BFS:\n";
    TeamMember* bfsResult = tree.bfsSearch("Grace Lee");
    if (bfsResult) {
        std::cout << "Found: ";
        bfsResult->display();
    }
    
    std::cout << "\n5. Searching for 'Henry Ford' with DFS:\n";
    TeamMember* dfsResult = tree.dfsSearch("Henry Ford");
    if (dfsResult) {
        std::cout << "Found: ";
        dfsResult->display();
    }
    
    std::cout << "\n6. Searching for non-existent member 'John Doe':\n";
    TeamMember* notFound = tree.bfsSearch("John Doe");
    if (!notFound) {
        std::cout << "Correctly not found!\n";
    }
    
    std::cout << "\n7. Removing member with ID 4 (David Wilson):\n";
    tree.removeMember(4);
    
    std::cout << "\n8. Displaying updated hierarchy:\n";
    tree.displayTree();
    
    std::cout << "\n=== Auto Test Completed ===\n";
}

int main() {
    HierarchyTree teamTree;
    int choice;
    
    do {
        showMenu();
        std::cin >> choice;
        
        switch(choice) {
            case 1:
                setRoot(teamTree);
                break;
                
            case 2:
                addMember(teamTree);
                break;
                
            case 3:
                removeMember(teamTree);
                break;
                
            case 4:
                teamTree.displayTree();
                break;
                
            case 5:
                searchBFS(teamTree);
                break;
                
            case 6:
                searchDFS(teamTree);
                break;
                
            case 7:
                autoTest(teamTree);
                break;
                
            case 8:
                std::cout << "Exiting program.\n";
                break;
                
            default:
                std::cout << "Invalid choice!\n";
        }
    } while(choice != 8);
    
    return 0;
}
