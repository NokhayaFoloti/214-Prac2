#ifndef ROUTESTRATEGY_H
#define ROUTESTRATEGY_H

#include <string>
#include <iostream>

// --- Abstract Strategy Base ---
class RouteStrategy {
public:
    virtual ~RouteStrategy() = default;
    virtual void calculateRoute(const std::string& origin, const std::string& destination) = 0;
    virtual std::string getName() const = 0;
};

// --- Concrete Strategies ---
class ShortestRouteStrategy : public RouteStrategy {
public:
    void calculateRoute(const std::string& origin, const std::string& destination) override;
    std::string getName() const override { return "Shortest Route (Minimal Distance)"; }
};

class FastestRouteStrategy : public RouteStrategy {
public:
    void calculateRoute(const std::string& origin, const std::string& destination) override;
    std::string getName() const override { return "Fastest Route (High Speed / Direct)"; }
};

class ScenicRouteStrategy : public RouteStrategy {
public:
    void calculateRoute(const std::string& origin, const std::string& destination) override;
    std::string getName() const override { return "Scenic Route (Landmarks & Vistas)"; }
};

// --- Context ---
class Trip {
private:
    std::string origin;
    std::string destination;
    RouteStrategy* strategy;

public:
    Trip(const std::string& origin, const std::string& destination, RouteStrategy* initialStrategy);
    virtual ~Trip();

    Trip(const Trip&) = delete;
    Trip& operator=(const Trip&) = delete;

    void plan();
    void setStrategy(RouteStrategy* newStrategy);
    void setEndpoints(const std::string& from, const std::string& to);

    std::string getOrigin() const { return origin; }
    std::string getDestination() const { return destination; }
    std::string getCurrentStrategyName() const;
};

#endif // ROUTESTRATEGY_H