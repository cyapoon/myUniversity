#ifndef EMPLOYEE_H
#define EMPLOYEE_H

using namespace std;

class Employee {
    private:
        char* name;
        double base_salary;
		
    public:
    /* TODO: Complete the member function declaration of the Employee class. 
	   Please refer to the figure on the lab website, use a virtual function
	   when there is an override, and remember to make the destructor virtual.
    */
   Employee(const char* name, double base_salary);
   Employee(const Employee &employee);
   virtual ~Employee();
   string get_name() const;
   double get_base_salary() const;
   virtual double get_salary() const;
   virtual void print() const;


       
};

#endif