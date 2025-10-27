#include "Animal.h"
#include<iostream>
using namespace std;

Animal::Animal(){cout << "constructor1" << endl;}
Animal::Animal(const std::string &name) : name(name) {cout << "constructor2" << endl;}

std::string Animal::get_name() const {
    return name;
}
