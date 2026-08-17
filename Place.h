#ifndef PLACE_H
#define PLACE_H

#include <string>
#include <vector>
#include <iostream>

// --- Abstract Component Base ---
class Place {
public:
    virtual ~Place() = default;
    virtual void display(int indent = 0) const = 0;
    virtual std::string getName() const = 0;
};

// --- Leaf ---
class Location : public Place {
private:
    std::string name;
    std::string description;

public:
    Location(const std::string& name, const std::string& description);
    virtual ~Location() = default;

    void display(int indent = 0) const override;
    std::string getName() const override { return name; }
    std::string getDescription() const { return description; }
};

// --- Composite ---
class Region : public Place {
private:
    std::string name;
    std::vector<Place*> children;

public:
    Region(const std::string& name);
    virtual ~Region();

    Region(const Region&) = delete;
    Region& operator=(const Region&) = delete;

    void add(Place* place);
    void remove(Place* place);

    void display(int indent = 0) const override;
    std::string getName() const override { return name; }
};

#endif // PLACE_H