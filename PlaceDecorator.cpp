#include "PlaceDecorator.h"
#include <iostream>

// ==================== Base Decorator ====================
PlaceDecorator::PlaceDecorator(Place* place) : wrappedPlace(place) {}

PlaceDecorator::~PlaceDecorator() {
    delete wrappedPlace;
    wrappedPlace = nullptr;
}

void PlaceDecorator::display(int indent) const {
    if (wrappedPlace) wrappedPlace->display(indent);
}

std::string PlaceDecorator::getName() const {
    return wrappedPlace ? wrappedPlace->getName() : "Unknown";
}

// ==================== Concrete Decorators ====================
WeatherDecorator::WeatherDecorator(Place* place, const std::string& weatherCondition)
    : PlaceDecorator(place), weatherCondition(weatherCondition) {}

void WeatherDecorator::display(int indent) const {
    PlaceDecorator::display(indent);
    std::string indentation(indent + 2, ' ');
    std::cout << indentation << "  * [Weather Effect]: " << weatherCondition << "\n";
}

TollDecorator::TollDecorator(Place* place, int tollFee)
    : PlaceDecorator(place), tollFee(tollFee) {}

void TollDecorator::display(int indent) const {
    PlaceDecorator::display(indent);
    std::string indentation(indent + 2, ' ');
    std::cout << indentation << "  * [Toll Booth]: Entry fee of " << tollFee << " gold coins.\n";
}

QuestDecorator::QuestDecorator(Place* place, const std::string& questTitle)
    : PlaceDecorator(place), questTitle(questTitle) {}

void QuestDecorator::display(int indent) const {
    PlaceDecorator::display(indent);
    std::string indentation(indent + 2, ' ');
    std::cout << indentation << "  * [Active Quest]: " << questTitle << "\n";
}