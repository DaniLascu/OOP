//
// Created by danie on 12/6/2023.
//

#ifndef OOP_LIVESTOCK_H
#define OOP_LIVESTOCK_H


#include <string>
#include <iostream>
class livestock {
protected:
    int animal_id;
    static int number_of_animals;
    std::string animal_name;
    int weight;
    const static std::string owner;

public:
    livestock(const std::string& name = "unknown", int Weight = 0);
    livestock(const livestock &other);
    virtual ~livestock();
    virtual void display();
    void set_weight(int kg);
    void set_name(const std::string& name);
    int get_weight();
    std::string get_name();

    static int getNumberOfAnimals();

    friend std::ostream &operator<<(std::ostream& out, const livestock& ob);
    livestock &operator=(const livestock &other);
    virtual double total_proffit() = 0;
    virtual  int getPrice() = 0;
};



#endif //OOP_LIVESTOCK_H
