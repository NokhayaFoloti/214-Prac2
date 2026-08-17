#ifndef TRAVELMODE_H
#define TRAVELMODE_H

#include <string>
#include <iostream>

class Traveller;

// --- Abstract State Base ---
class TravelMode {
public:
    virtual ~TravelMode() = default;
    virtual void move(Traveller* context) = 0;
    virtual void switchMode(Traveller* context, const std::string& targetMode) = 0;
    virtual std::string getName() const = 0;
};

// --- Concrete States ---
class WalkingMode : public TravelMode {
public:
    void move(Traveller* context) override;
    void switchMode(Traveller* context, const std::string& targetMode) override;
    std::string getName() const override { return "On Foot (Walking)"; }
};

class BikingMode : public TravelMode {
public:
    void move(Traveller* context) override;
    void switchMode(Traveller* context, const std::string& targetMode) override;
    std::string getName() const override { return "Bicycle"; }
};

class DrivingMode : public TravelMode {
public:
    void move(Traveller* context) override;
    void switchMode(Traveller* context, const std::string& targetMode) override;
    std::string getName() const override { return "Motor Vehicle (Driving)"; }
};

// --- Context ---
class Traveller {
private:
    std::string name;
    TravelMode* currentMode;
    int stamina;
    int fuel;

public:
    Traveller(const std::string& name, int initialStamina = 50, int initialFuel = 60);
    virtual ~Traveller();

    Traveller(const Traveller&) = delete;
    Traveller& operator=(const Traveller&) = delete;

    void move();
    void requestModeChange(const std::string& newMode);
    void setMode(TravelMode* newMode);

    int getStamina() const { return stamina; }
    void useStamina(int amount);
    void restoreStamina(int amount);

    int getFuel() const { return fuel; }
    void useFuel(int amount);
    void refuel(int amount);

    std::string getName() const { return name; }
    std::string getCurrentModeName() const;
};

#endif // TRAVELMODE_H