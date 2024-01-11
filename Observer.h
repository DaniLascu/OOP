//
// Created by danie on 1/4/2024.
//

#ifndef OOP_OBSERVER_H
#define OOP_OBSERVER_H

class Culture;

class Observer{
public:
    virtual void update(Culture* culture) = 0;
};
#endif //OOP_OBSERVER_H
