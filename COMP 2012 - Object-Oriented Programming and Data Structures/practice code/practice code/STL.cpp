#include<iostream>
using namespace std;
#include<array>
#include<vector>
#include<set>


int main()
{

    array<float,5> arr = {1.2,2.3,3.4,4.5,5.6};
    

    for(float i: arr)
    {
        cout << i << endl;
    }

    vector<int> v = {1,2,3,4,5};


    set<int> s = {1,2,3,4,5};
    
    for(set<int>::iterator it = s.begin(); it != s.end();it++)
    {
        cout << *it << endl;
    }
    


    return 0;
}