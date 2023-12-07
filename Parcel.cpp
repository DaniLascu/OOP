//
// Created by danie on 12/6/2023.
//

#include "Parcel.h"
#include <iostream>

int parcel::Id = 0;

parcel::parcel(long double size) : parcel_id(Id), occupied_area(0) {
    this->size = size;
    Id++;
}

parcel::parcel(const parcel& other) {
    parcel_id = other.parcel_id;
    size = other.size;
    occupied_area = other.occupied_area;
}

parcel::~parcel() {
    // Destructor implementation (if needed)
}

void parcel::display_parcel() {
    std::cout << "Id zona " << parcel_id << "\n";
    std::cout << "Dimensiune parcela " << size << "\n";
    std::cout << "Dimensiune ocupata " << occupied_area << "\n";
}

int parcel::getParcelId() const {
    return parcel_id;
}

void parcel::setParcelId(int parcelId) {
    parcel_id = parcelId;
}

long double parcel::getSize() const {
    return size;
}

void parcel::setSize(long double local_size) {
    parcel::size = local_size;
}

long double parcel::getOccupiedArea() const {
    return occupied_area;
}

void parcel::setOccupiedArea(long double occupiedArea) {
    occupied_area = occupied_area + occupiedArea;
}

int parcel::getId() {
    return Id;
}

std::ostream& operator<<(std::ostream& out, const parcel& ob) {
    out << "Id: " << ob.parcel_id << std::endl;
    out << "Size: " << ob.size << std::endl;
    out << "Zona ocupata: " << ob.occupied_area << std::endl;
    return out;
}

parcel& parcel::operator=(const parcel& other) {
    if (this == &other) {
        return *this; // Handle self-assignment
    }
    // Copy data members from 'other' to 'this'
    parcel_id = other.parcel_id;
    size = other.size;
    occupied_area = other.occupied_area;
    return *this;
}
