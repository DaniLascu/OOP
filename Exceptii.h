//
// Created by danie on 12/7/2023.
//

#ifndef OOP_EXCEPTII_H
#define OOP_EXCEPTII_H
#include <exception>

class Profit_sub_unit : public std::exception {
public:
    const char* what() const throw() {
        return "Profitul trebuie sa fie < 1";
    }
};

class OptiuneInvalida : public std::exception {
public:
    const char* what() const throw() {
        return "Optiune invalida!";
    }
};

class NotEnoughFor1 : public std::exception {
public:
    const char* what() const throw() override {
        return "Nu este destul spatiu pentru 1 planta!\n";
    }
};

class NrTooLarge : public std::exception {
public:
    const char* what() const throw() override {
        return "Nr de plante ales este prea mare!\n";
    }
};

class NotMoney : public std::exception {
public:
    const char* what() const throw() override {
        return "Nu ai destui bani\n";
    }
};
#endif //OOP_EXCEPTII_H
