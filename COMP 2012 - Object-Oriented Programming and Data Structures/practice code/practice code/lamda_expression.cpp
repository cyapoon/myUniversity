#include<iostream>
using namespace std;

//global funtion: square()
int square(int k)
{
    return k*k;
}

int main()
{   
    auto f = [](int k){return k*k;};

    //call fucntion square()
    cout << f(10) << endl;

    //lamda expression
    cout << [] (int k) {return k*k;} (10) << endl;

    int range[] = {1,2,7};
    for(int i=0;i<sizeof(range)/sizeof(int);i++)
        cout << square(range[i]) << endl;

    //lamda expression
    for(int v:range)
        cout << [] (int k){return k*k;}(v) << endl;

    


    return 0;
}