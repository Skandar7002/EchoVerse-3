#ifndef HIERARCHYTREE_H
#define HIERARCHYTREE_H

#include "teammember.h"
#include <string>

struct QueueNode {
    TeamMember* member;
    QueueNode* next;
    QueueNode(TeamMember* m);
};

struct StackNode {
    TeamMember* member;
    StackNode* next;
    StackNode(TeamMember* m);
};

class HierarchyTree {
private:
    TeamMember* root;
    int nextId;
    
    // Helper functions
    TeamMember* findMemberById(TeamMember* current, int id);
    TeamMember* findMemberByName(TeamMember* current, const std::string& name);
    void deleteSubtree(TeamMember* member);
    void displayHelper(TeamMember* member, int depth);
    int countChildren(TeamMember* member);
    
    // Queue for BFS
    QueueNode* front;
    QueueNode* rear;
    void enqueue(TeamMember* member);
    TeamMember* dequeue();
    bool isQueueEmpty();
    void clearQueue();
    
    // Stack for DFS
    StackNode* top;
    void push(TeamMember* member);
    TeamMember* pop();
    bool isStackEmpty();
    void clearStack();
    
public:
    HierarchyTree();
    ~HierarchyTree();
    
    // Core operations
    void setRoot(const std::string& name, const std::string& role);
    bool addMember(int parentId, const std::string& name, const std::string& role);
    bool removeMember(int id);
    
    // Search operations
    TeamMember* bfsSearch(const std::string& name);
    TeamMember* dfsSearch(const std::string& name);
    
    // Display
    void displayTree();
    
    // Utility
    bool isEmpty() const;
    TeamMember* getRoot() const;
    int generateId();
};

#endif
