//
// Created by danie on 1/9/2024.
//

#ifndef OOP_ANIMALFACTORY_H
#define OOP_ANIMALFACTORY_H

#include <iostream>
#include <memory>
#include "Cow.h"
#include "Chicken.h"
#include "Sheep.h"

class AnimalFactory {
public:
    std::shared_ptr<livestock> build(int optiune, double &profit);
};

#endif //OOP_ANIMALFACTORY_H
