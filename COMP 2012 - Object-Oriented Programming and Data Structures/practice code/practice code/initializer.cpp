#include<iostream>
using namespace std;


int main()
{
    int w = 3.4;
    int x1 {6};
    int x2 = {8};
    int y {'k'};
    // int z{3.4};     error

    cout << "w = " << w << endl;
    cout << "x1 = " <<  x1 << endl;
    cout << "x2 = " << x2 << endl;
    cout << "y = " << y << endl;
    //cout << "z = " << z << endl;

    int &ww = w;
    int &www {ww};
    www = 123;
    cout << "www = " << www << endl;
    cout << "w = " << w << endl;


    const char s1[] = "Steve Jobs";    // '\0' automatically added
    const char s2[] {"Bill Gates"};    // '\0' automatically added
    const char s3[] = {'h','k','u','s','t','\0'};
    const char s4[]  {'h','k','u','s','t','\0'};
    
    cout << "s1 = " << s1 << endl;
    cout << "s2 = " << s2 << endl;
    cout << "s3 = " << s3 << endl;
    cout << "s4 = " << s4 << endl;




    return 0;
}