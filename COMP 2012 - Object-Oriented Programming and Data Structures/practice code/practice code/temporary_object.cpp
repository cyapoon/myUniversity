#include<iostream>
using namespace std;

class X
{
public:
    X() {cout << "X(). "<< this << endl;}
    X(int a){cout << "X(int), "<< this << endl;}
    X(const X& other){cout << "X(const X&), " << this << endl;}
    ~X() {cout << "~X(), " << this << endl;}
};

int main()
{
    cout << "Beginning of main\n";
    X obj1;
    X obj2 = X(100);// temporary object
    cout << "Ending of main\n";

    return 0;
}