#include "Place.h"
#include <iostream>
#include <algorithm>

// ==================== Location (Leaf) ====================
Location::Location(const std::string& name, const std::string& description)
    : name(name), description(description) {}

void Location::display(int indent) const {
    std::string indentation(indent, ' ');
    std::cout << indentation << "[Location] " << name << " - " << description << "\n";
}

// ==================== Region (Composite) ====================
Region::Region(const std::string& name) : name(name) {}

Region::~Region() {
    for (Place* child : children) {
        delete child;
    }
    children.clear();
}

void Region::add(Place* place) {
    if (place) {
        children.push_back(place);
    }
}

void Region::remove(Place* place) {
    auto it = std::find(children.begin(), children.end(), place);
    if (it != children.end()) {
        delete *it;
        children.erase(it);
    }
}

void Region::display(int indent) const {
    std::string indentation(indent, ' ');
    std::cout << indentation << "+ [Region] " << name << ":\n";
    for (const Place* child : children) {
        if (child) {
            child->display(indent + 4);
        }
    }
}