#ifndef CONTRACT_H
#define CONTRACT_H

#include <string>
#include "Employee.h"

using namespace std;

class Contract : public Employee{
    private:
        int working_hours;
        double hourly_rate;
    
	public:
    /* TODO: Complete the member function declaration of the Contract class
	         based on the given functions on the web page.
    */
        Contract(const char* name, double base_salary, int working_hours, double hourly_rate);
        ~Contract();
        int get_working_hours() const;
        double get_hourly_rate() const;
        double get_salary() const;
        void print() const;

        void info() const; // This function is used to test dynamic_cast, it only exists in Contract type
};

#endif
