#include "hierarchytree.h"
#include <iostream>

QueueNode::QueueNode(TeamMember* m) : member(m), next(nullptr) {}

StackNode::StackNode(TeamMember* m) : member(m), next(nullptr) {}

HierarchyTree::HierarchyTree() : root(nullptr), nextId(1), 
                                  front(nullptr), rear(nullptr), top(nullptr) {}

HierarchyTree::~HierarchyTree() {
    deleteSubtree(root);
    clearQueue();
    clearStack();
}

void HierarchyTree::setRoot(const std::string& name, const std::string& role) {
    if (root) {
        std::cout << "Root already exists!" << std::endl;
        return;
    }
    root = new TeamMember(generateId(), name, role);
    std::cout << "Root set: " << name << " (" << role << ")" << std::endl;
}

bool HierarchyTree::addMember(int parentId, const std::string& name, const std::string& role) {
    if (!root) {
        std::cout << "Error: Tree has no root!" << std::endl;
        return false;
    }
    
    TeamMember* parent = findMemberById(root, parentId);
    if (!parent) {
        std::cout << "Parent with ID " << parentId << " not found!" << std::endl;
        return false;
    }
    
    TeamMember* newMember = new TeamMember(generateId(), name, role);
    newMember->parent = parent;
    
    if (!parent->firstChild) {
        parent->firstChild = newMember;
    } else {
        TeamMember* current = parent->firstChild;
        while (current->nextSibling) {
            current = current->nextSibling;
        }
        current->nextSibling = newMember;
    }
    
    std::cout << "Added " << name << " under " << parent->name << std::endl;
    return true;
}

bool HierarchyTree::removeMember(int id) {
    if (!root) return false;
    
    if (root->id == id) {
        std::cout << "Cannot remove root member!" << std::endl;
        return false;
    }
    
    TeamMember* member = findMemberById(root, id);
    if (!member) return false;
    
    TeamMember* parent = member->parent;
    
    if (parent->firstChild == member) {
        parent->firstChild = member->nextSibling;
    } else {
        TeamMember* sibling = parent->firstChild;
        while (sibling->nextSibling != member) {
            sibling = sibling->nextSibling;
        }
        sibling->nextSibling = member->nextSibling;
    }
    
    deleteSubtree(member);
    std::cout << "Removed member with ID " << id << std::endl;
    return true;
}

TeamMember* HierarchyTree::bfsSearch(const std::string& name) {
    if (!root) return nullptr;
    
    clearQueue();
    enqueue(root);
    
    while (!isQueueEmpty()) {
        TeamMember* current = dequeue();
        
        if (current->name == name) {
            clearQueue();
            return current;
        }
        
        TeamMember* child = current->firstChild;
        while (child) {
            enqueue(child);
            child = child->nextSibling;
        }
    }
    
    return nullptr;
}

TeamMember* HierarchyTree::dfsSearch(const std::string& name) {
    if (!root) return nullptr;
    
    clearStack();
    push(root);
    
    while (!isStackEmpty()) {
        TeamMember* current = pop();
        
        if (current->name == name) {
            clearStack();
            return current;
        }
        
        TeamMember* child = current->firstChild;
        TeamMember* lastChild = nullptr;
        
        while (child) {
            lastChild = child;
            child = child->nextSibling;
        }
        
        child = current->firstChild;
        while (child) {
            push(child);
            child = child->nextSibling;
        }
    }
    
    return nullptr;
}

void HierarchyTree::displayTree() {
    if (!root) {
        std::cout << "Tree is empty!" << std::endl;
        return;
    }
    
    std::cout << "\n=== Team Hierarchy ===\n";
    displayHelper(root, 0);
}

bool HierarchyTree::isEmpty() const {
    return root == nullptr;
}

TeamMember* HierarchyTree::getRoot() const {
    return root;
}

int HierarchyTree::generateId() {
    return nextId++;
}

TeamMember* HierarchyTree::findMemberById(TeamMember* current, int id) {
    if (!current) return nullptr;
    if (current->id == id) return current;
    
    TeamMember* found = findMemberById(current->firstChild, id);
    if (found) return found;
    
    return findMemberById(current->nextSibling, id);
}

TeamMember* HierarchyTree::findMemberByName(TeamMember* current, const std::string& name) {
    if (!current) return nullptr;
    if (current->name == name) return current;
    
    TeamMember* found = findMemberByName(current->firstChild, name);
    if (found) return found;
    
    return findMemberByName(current->nextSibling, name);
}

void HierarchyTree::deleteSubtree(TeamMember* member) {
    if (!member) return;
    
    deleteSubtree(member->firstChild);
    deleteSubtree(member->nextSibling);
    
    delete member;
}

void HierarchyTree::displayHelper(TeamMember* member, int depth) {
    if (!member) return;
    
    for (int i = 0; i < depth; i++) {
        std::cout << "  ";
        if (i == depth - 1) std::cout << "+-";
    }
    
    member->display();
    
    displayHelper(member->firstChild, depth + 1);
    displayHelper(member->nextSibling, depth);
}

int HierarchyTree::countChildren(TeamMember* member) {
    int count = 0;
    TeamMember* child = member->firstChild;
    while (child) {
        count++;
        child = child->nextSibling;
    }
    return count;
}

void HierarchyTree::enqueue(TeamMember* member) {
    QueueNode* newNode = new QueueNode(member);
    if (!rear) {
        front = rear = newNode;
    } else {
        rear->next = newNode;
        rear = newNode;
    }
}

TeamMember* HierarchyTree::dequeue() {
    if (!front) return nullptr;
    
    QueueNode* temp = front;
    TeamMember* member = front->member;
    front = front->next;
    
    if (!front) rear = nullptr;
    
    delete temp;
    return member;
}

bool HierarchyTree::isQueueEmpty() {
    return front == nullptr;
}

void HierarchyTree::clearQueue() {
    while (!isQueueEmpty()) {
        dequeue();
    }
}

void HierarchyTree::push(TeamMember* member) {
    StackNode* newNode = new StackNode(member);
    newNode->next = top;
    top = newNode;
}

TeamMember* HierarchyTree::pop() {
    if (!top) return nullptr;
    
    StackNode* temp = top;
    TeamMember* member = top->member;
    top = top->next;
    
    delete temp;
    return member;
}

bool HierarchyTree::isStackEmpty() {
    return top == nullptr;
}

void HierarchyTree::clearStack() {
    while (!isStackEmpty()) {
        pop();
    }
}
