#include "TravelMode.h"
#include <iostream>

// ==================== WalkingMode ====================
void WalkingMode::move(Traveller* context) {
    std::cout << "[" << context->getName() << "] walks steadily. Stamina slowly recovers (+5).\n";
    context->restoreStamina(5);
}

void WalkingMode::switchMode(Traveller* context, const std::string& targetMode) {
    if (targetMode == "bike") {
        if (context->getStamina() >= 20) {
            std::cout << "-> Mounting bicycle (Stamina: " << context->getStamina() << " >= 20).\n";
            context->setMode(new BikingMode());
        } else {
            std::cout << "[Guard Blocked] Too exhausted to ride a bicycle (Stamina: " 
                      << context->getStamina() << "/20 required).\n";
        }
    } else if (targetMode == "drive") {
        if (context->getFuel() >= 30) {
            std::cout << "-> Starting car engine (Fuel: " << context->getFuel() << " >= 30).\n";
            context->setMode(new DrivingMode());
        } else {
            std::cout << "[Guard Blocked] Not enough fuel to drive (Fuel: " 
                      << context->getFuel() << "/30 required).\n";
        }
    } else if (targetMode == "walk") {
        std::cout << "Already walking.\n";
    } else {
        std::cout << "Unknown travel mode: " << targetMode << "\n";
    }
}

// ==================== BikingMode ====================
void BikingMode::move(Traveller* context) {
    std::cout << "[" << context->getName() << "] pedals briskly along the path (-15 stamina).\n";
    context->useStamina(15);

    if (context->getStamina() <= 0) {
        std::cout << "[Exhaustion] Out of stamina! Falling back to walking...\n";
        context->setMode(new WalkingMode());
    }
}

void BikingMode::switchMode(Traveller* context, const std::string& targetMode) {
    if (targetMode == "walk") {
        std::cout << "-> Dismounting bicycle to walk.\n";
        context->setMode(new WalkingMode());
    } else if (targetMode == "drive") {
        if (context->getFuel() >= 30) {
            std::cout << "-> Stowing bicycle and getting into car.\n";
            context->setMode(new DrivingMode());
        } else {
            std::cout << "[Guard Blocked] Not enough fuel to drive.\n";
        }
    } else if (targetMode == "bike") {
        std::cout << "Already riding bicycle.\n";
    }
}

// ==================== DrivingMode ====================
void DrivingMode::move(Traveller* context) {
    std::cout << "[" << context->getName() << "] drives forward at high speed (-20 fuel).\n";
    context->useFuel(20);

    if (context->getFuel() <= 0) {
        std::cout << "[Empty Tank] Car sputtered out! Continuing on foot...\n";
        context->setMode(new WalkingMode());
    }
}

void DrivingMode::switchMode(Traveller* context, const std::string& targetMode) {
    if (targetMode == "walk") {
        std::cout << "-> Parking car and proceeding on foot.\n";
        context->setMode(new WalkingMode());
    } else if (targetMode == "bike") {
        if (context->getStamina() >= 20) {
            std::cout << "-> Parking car and switching to bicycle.\n";
            context->setMode(new BikingMode());
        } else {
            std::cout << "[Guard Blocked] Too exhausted to ride a bicycle.\n";
        }
    } else if (targetMode == "drive") {
        std::cout << "Already driving.\n";
    }
}

// ==================== Traveller (Context) ====================
Traveller::Traveller(const std::string& name, int initialStamina, int initialFuel)
    : name(name), currentMode(new WalkingMode()), stamina(initialStamina), fuel(initialFuel) {}

Traveller::~Traveller() {
    delete currentMode;
    currentMode = nullptr;
}

void Traveller::move() {
    if (currentMode) currentMode->move(this);
}

void Traveller::requestModeChange(const std::string& newMode) {
    if (currentMode) currentMode->switchMode(this, newMode);
}

void Traveller::setMode(TravelMode* newMode) {
    if (currentMode != newMode) {
        delete currentMode;
        currentMode = newMode;
    }
}

void Traveller::useStamina(int amount) {
    stamina -= amount;
    if (stamina < 0) stamina = 0;
}

void Traveller::restoreStamina(int amount) {
    stamina += amount;
    if (stamina > 100) stamina = 100;
}

void Traveller::useFuel(int amount) {
    fuel -= amount;
    if (fuel < 0) fuel = 0;
}

void Traveller::refuel(int amount) {
    fuel += amount;
    if (fuel > 100) fuel = 100;
}

std::string Traveller::getCurrentModeName() const {
    return currentMode ? currentMode->getName() : "None";
}