//
// Created by danie on 12/6/2023.
//
#include "livestock.h"
#include <string>
#include  <iostream>

int livestock::number_of_animals = 0;  // Initialize the static member variable

const std::string livestock::owner = "Dani";  // Initialize the static member variable

livestock::livestock(const std::string &name, int Weight) : animal_id(number_of_animals++) {
    this->animal_name = name;
    this->weight = Weight;
}

livestock::livestock(const livestock &other) : animal_id(other.animal_id), animal_name(other.animal_name), weight(other.weight) {
}

livestock::~livestock() {
    // Destructor implementation (if needed)
}

void livestock::display() {
    std::cout << "Animal ID: " << animal_id << std::endl;
    std::cout << "Name: " << animal_name << std::endl;
    std::cout << "Weight: " << weight << " kg" << std::endl;
}

void livestock::set_weight(int kg) {
    weight = kg;
}

void livestock::set_name(const std::string &name) {
    animal_name = name;
}

int livestock::get_weight() {
    return weight;
}

std::string livestock::get_name() {
    return animal_name;
}

int livestock::getNumberOfAnimals() {
    return number_of_animals;
}

std::ostream &operator<<(std::ostream &out, const livestock &ob) {
    out << "Animal ID: " << ob.animal_id << "\nName: " << ob.animal_name << "\nWeight: " << ob.weight << " kg";
    return out;
}

livestock &livestock::operator=(const livestock &other) {
    if (this != &other) {
        animal_id = other.animal_id;
        animal_name = other.animal_name;
        weight = other.weight;
    }
    return *this;
}

// You need to implement the pure virtual function total_proffit() in the derived classes.
// Add the implementation for the specific derived classes.


