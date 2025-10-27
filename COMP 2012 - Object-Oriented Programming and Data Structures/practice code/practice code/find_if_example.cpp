#include<iostream>
using namespace std;
#include<vector>
#include<algorithm>

bool f(int a)
{
    return (a%2);
}

void print(int a)
{
    cout << "~" << a << "~";
}

bool compare(int a, int b)
{
    return a>b;
}

int main()
{

    vector<int> v {2,3,6,7,9};
    // find_if()
    vector<int>::iterator it;
    it = find_if(v.begin(), v.end(),f);
    cout << *it << endl;

    // for_each()
    for_each(v.begin(),v.end(),print);
    cout << endl;

    //replace()
    replace(v.begin(),v.end(),2,20);
    for_each(v.begin(),v.end(),print);
    cout << endl;

    // sort()
    sort(v.begin(),v.end(),compare);
    for_each(v.begin(),v.end(),print);
    cout << endl;
    

    return 0;
}