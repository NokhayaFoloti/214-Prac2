#include "RouteStrategy.h"
#include <iostream>

// ==================== Concrete Strategies ====================
void ShortestRouteStrategy::calculateRoute(const std::string& origin, const std::string& destination) {
    std::cout << "[Route Planner] Calculating shortest direct distance from " 
              << origin << " to " << destination << "...\n"
              << "  -> Path: Direct straight-line path selected (minimizing total distance).\n";
}

void FastestRouteStrategy::calculateRoute(const std::string& origin, const std::string& destination) {
    std::cout << "[Route Planner] Calculating fastest route from " 
              << origin << " to " << destination << "...\n"
              << "  -> Path: High-speed motorways and clear avenues prioritized.\n";
}

void ScenicRouteStrategy::calculateRoute(const std::string& origin, const std::string& destination) {
    std::cout << "[Route Planner] Calculating most scenic route from " 
              << origin << " to " << destination << "...\n"
              << "  -> Path: Winding through riversides, ancient forests, and viewpoints.\n";
}

// ==================== Trip (Context) ====================
Trip::Trip(const std::string& origin, const std::string& destination, RouteStrategy* initialStrategy)
    : origin(origin), destination(destination), strategy(initialStrategy) {}

Trip::~Trip() {
    delete strategy;
    strategy = nullptr;
}

void Trip::setStrategy(RouteStrategy* newStrategy) {
    if (strategy != newStrategy) {
        delete strategy;
        strategy = newStrategy;
    }
}

void Trip::plan() {
    if (strategy) {
        strategy->calculateRoute(origin, destination);
    } else {
        std::cout << "[Trip] No route strategy selected!\n";
    }
}

void Trip::setEndpoints(const std::string& from, const std::string& to) {
    origin = from;
    destination = to;
}

std::string Trip::getCurrentStrategyName() const {
    return strategy ? strategy->getName() : "None";
}