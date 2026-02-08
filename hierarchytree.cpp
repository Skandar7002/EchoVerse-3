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
