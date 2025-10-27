#include<iostream>
using namespace std;

class Complex
{
private:
    float real;
    float imag;

public:
    Complex(float r, float i) {real = r; imag = i;}
    void print() const {cout << "(" << real << ","<< imag << ")" << endl;}
    Complex add1(const Complex x)
    {
        real += x.real;
        imag += x.imag;
        return (*this);
    }

    Complex* add2(const Complex* x)
    {
        real += x->real;
        imag += x->imag;
        return (this);
    }

    Complex& add3(const Complex& x)
    {
        real += x.real;
        imag += x.imag;
        return (*this);
    }
};

int main()
{
    Complex a {2,3};
    Complex b(4,5);
    Complex c = a.add1(b);
    c.print();
    a.print();
    a.add1(b);
    a.print();
    a.add2(&b);
    a.print();
    a.add3(b);
    a.print();
    c.print();
    return 0;
}