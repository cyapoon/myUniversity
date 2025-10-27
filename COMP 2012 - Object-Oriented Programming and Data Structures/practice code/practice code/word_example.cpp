#include<iostream>
#include<cstring>
using namespace std;

class Word
{
private:
    int frequency;
    char* str;
public:
    Word(){cout << "Word()\n"; frequency = 0; str = nullptr;} //default constructor
    Word(const char* s, int n = 0){frequency = n;str = new char[strlen(s)+1]; strcpy(str,s);} //conversion constructor
    Word(const Word &w){ str = nullptr; set(w.frequency, w.str);}
    void print() const{
        if(str){cout << frequency << " " << str <<endl;}}
    void set(int n, char* s)
    {
        frequency = n;
        if(str)
        {
            delete [] str;
        }
        if(s)
        {
            str = new char[strlen(s)+1];
            strcpy(str,s);
        }
        else
        {
            str = nullptr;
        }
    }
};

int main()
{
    Word w1{"COMP2012"};
    Word w2 = "COMP2012H";
    w1.print();
    w2.print();
    Word w3 = w1;
    w3.print();

    return 0;
}