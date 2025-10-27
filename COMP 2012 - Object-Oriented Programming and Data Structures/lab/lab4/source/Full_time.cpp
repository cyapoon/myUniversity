#include <iostream>
#include "Full_time.h"

using namespace std;

// TODO: Complete the constructor of Full_time class. 
//       Remember to call the constructor of base class, use new to initialize char*position.
Full_time::Full_time(const char* name, double base_salary, const char* position, int seniority, double bonus):
Employee(name,base_salary), seniority(seniority),bonus(bonus)
{
    this->position = new char[strlen(position)+1];
    strcpy(this->position,position);
    // this->seniority = seniority;
    // this->bonus = bonus;
}


Full_time::~Full_time() {
    cout << "Call destructor of Full_time" << endl;
// TODO: dynamic memory deallocation
    delete [] this->position;
    this->position = nullptr;
}

// TODO: Complete Full_time::get_position
string Full_time::get_position() const{
    return this->position;
}

// TODO: Complete Full_time::get_seniority
int Full_time::get_seniority() const{
    return this->seniority;
}

// TODO: Complete Full_time::get_bonus
double Full_time::get_bonus() const{
    return this->bonus;
}

// TODO: Complete Full_time::get_salary. Salary = base_salary + 0.1 * base_salary * seniority + bonus
double Full_time::get_salary() const{
    return (get_base_salary() + 0.1*get_base_salary()*get_seniority() + get_bonus());
}

void Full_time::print() const{
    cout << "Full_time employee: " << get_name() << ", position: " << get_position() << endl;
    cout << "Salary: " << get_salary() << endl;
}