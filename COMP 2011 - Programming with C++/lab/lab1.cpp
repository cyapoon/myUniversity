#include <iostream>
using namespace std;
  
int main()
{
    /*
        There are 6 errors in total. Can you catch them all? :)
  
        See the expected output section on the lab page to see what is expected from the corrected program.
    */
  
    int number;      //add a ";"
    cout << "Welcome to the exciting, fun, and awesome programming world! "
         << "Enter an odd number, and I can tell something about you! "  << endl;  //add "<<"
    cin >> number;    //change "<<" to ">>"
  
    if (number % 2 == 0)   //change "=" to "==" 
        cout << "Hmm... this is not an odd number..." << endl;
    
    else
    {
        if (number < 0)    //change "num" to "number"
            cout << "You seem to be a bit negative... :( Cheer up! " << endl;
        else
            cout << "You must be very excited! Me too! :)" << endl;
    } //add a "}"
    return 0;
}