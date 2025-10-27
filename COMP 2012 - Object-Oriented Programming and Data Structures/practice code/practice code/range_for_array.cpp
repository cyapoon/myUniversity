#include<iostream>
using namespace std;


int main()
{
    int arr[] {10,5,20,25,0};

    // for (int i = 0; i < sizeof(arr)/sizeof(int); i++)
    // {cout << arr[i] << endl;}

    // for(int k: arr)   // k copies the element values
    //     ++k;     //change the copy

    // for(int k:arr)
    //     cout << k << " ";
    // cout << endl;

    for(int &k: arr)   // k is an alias of the element value
        ++k;     //change the values

    for(int k:arr)
        cout << k << " ";
    cout << endl;

    return 0;

}