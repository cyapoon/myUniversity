#include <iostream>
#include "Employee.h"
#include <cstring>

using namespace std;

//TODO: Complete conversion constructor
Employee::Employee(const char* name, double base_salary):base_salary(base_salary)
{
    this->name = new char[strlen(name)+1];
    strcpy(this->name,name);
    //this->base_salary = base_salary;
}



//TODO: Complete copy constructor
Employee::Employee(const Employee & employee):base_salary(employee.base_salary)
{
    this->name = new char[strlen(employee.name)+1];
    strcpy(this->name,employee.name);
    
}



Employee::~Employee(){
    cout << "Call destructor of Employee" <<endl;
// TODO: dynamic memory deallocation
    delete [] this->name;
    this->name = nullptr; 

}

// TODO: Complete Employee::get_name
string Employee::get_name() const{
    return this->name;
}

// TODO: Complete Employee::get_base_salary
double Employee::get_base_salary() const{
    return this->base_salary;
}

// TODO: Complete Employee::get_salary. In the base class, salary is equal to base salary.
double Employee::get_salary() const{
    return this->base_salary;
}

void Employee::print() const{
    cout << "Employee: " << get_name() << endl;
    cout << "Salary: " << get_salary() << endl;
}