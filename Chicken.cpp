//
// Created by danie on 12/6/2023.
//

#include "Chicken.h"
#include <iostream>

int Chicken::price = 100;  // Set a default price for Chicken

Chicken::Chicken(int local_eggs, double local_price, double local_proffit, const std::string& name, int Weight)
        : livestock(name, Weight),
          number_of_eggs_day(local_eggs),
          price_per_egg(local_price),
          proffit_per_egg(local_proffit) {
}

Chicken::Chicken(const Chicken& other)
        : livestock(other),
          number_of_eggs_day(other.number_of_eggs_day),
          price_per_egg(other.price_per_egg),
          proffit_per_egg(other.proffit_per_egg) {
}

Chicken::~Chicken() {
    // Destructor implementation (if needed)
}

void Chicken::display() {
    livestock::display();
    std::cout << "Numar de oua pe zi: " << this->number_of_eggs_day << std::endl;
    std::cout << "Pret pentru un ou: " << this->price_per_egg << std::endl;
    std::cout << "Profit / ou: " << this->proffit_per_egg << std::endl;
}

int Chicken::getNumberOfEggsDay() const {
    return number_of_eggs_day;
}

void Chicken::setNumberOfEggsDay(int numberOfEggsDay) {
    number_of_eggs_day = numberOfEggsDay;
}

double Chicken::getPricePerEgg() const {
    return price_per_egg;
}

void Chicken::setPricePerEgg(double pricePerEgg) {
    price_per_egg = pricePerEgg;
}

double Chicken::getProffitPerEgg() const {
    return proffit_per_egg;
}

void Chicken::setProffitPerEgg(double proffitPerEgg) {
    proffit_per_egg = proffitPerEgg;
}

double Chicken::total_proffit() {
    return (this->number_of_eggs_day * this->price_per_egg * this->proffit_per_egg);
}

int Chicken::getPrice() {
    return price;
}