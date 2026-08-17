#ifndef PLACEDECORATOR_H
#define PLACEDECORATOR_H

#include "Place.h"
#include <string>

// --- Abstract Decorator Base ---
class PlaceDecorator : public Place {
protected:
    Place* wrappedPlace;

public:
    PlaceDecorator(Place* place);
    virtual ~PlaceDecorator();

    PlaceDecorator(const PlaceDecorator&) = delete;
    PlaceDecorator& operator=(const PlaceDecorator&) = delete;

    void display(int indent = 0) const override;
    std::string getName() const override;
};

// --- Concrete Decorators ---
class WeatherDecorator : public PlaceDecorator {
private:
    std::string weatherCondition;

public:
    WeatherDecorator(Place* place, const std::string& weatherCondition);
    void display(int indent = 0) const override;
};

class TollDecorator : public PlaceDecorator {
private:
    int tollFee;

public:
    TollDecorator(Place* place, int tollFee);
    void display(int indent = 0) const override;
};

class QuestDecorator : public PlaceDecorator {
private:
    std::string questTitle;

public:
    QuestDecorator(Place* place, const std::string& questTitle);
    void display(int indent = 0) const override;
};

#endif // PLACEDECORATOR_H