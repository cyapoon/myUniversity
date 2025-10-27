#ifndef FULL_TIME_H
#define FULL_TIME_H

#include <cstring>
#include "Employee.h"

using namespace std;

class Full_time : public Employee{
    private:
        char* position;
        int seniority; // The length of working years. A longer working
                       // years yield a higher salary in general. Eg, 
                       // seniority = 5 means working for 5 years.
        double bonus;
    public:
    /*TODO:complete the member function declaration of Full_time class
      based on the given functions on the web page.
    */
        Full_time(const char* name, double base_salary, const char* position, int seniority, double bonus);
        ~Full_time();
        string get_position() const;
        int get_seniority() const;
        double get_bonus() const;
        double get_salary() const;
        void print() const;




};
#endif