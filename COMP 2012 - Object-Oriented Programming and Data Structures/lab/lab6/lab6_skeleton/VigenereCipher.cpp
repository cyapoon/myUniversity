#include "VigenereCipher.h"
#include "Utility.h"

// TODO #1
// Initialize the static data member alphabetSize here
const int VigenereCipher:: alphabetSize = 26;

// TODO #2
// Implement the encrypt member function according to the given algoirthm.
string VigenereCipher:: encrypt(string plaintextMsg) const 
{
    string cipherText = "";
    char temp = '\0';
    for(int i = 0; i < plaintextMsg.size(); i++)
    {
        temp = plaintextMsg[i];
        //cout << temp << endl;
        if (temp >= 'A' && temp <= 'Z')
        {
            temp += ('a'-'A');
            //cout << "loop: " << i << " " << temp << endl;
        }
        //cout << temp << endl;
        if(temp >= 'a' && temp <= 'z')
        {
            //cout << "before:" << (int)temp << endl;
            int index = i%(key.size());
            //cout << "index=" << index << endl;
            temp -= 'a';
            temp += (key[index] - 'a');
            temp = temp % alphabetSize;
            temp += 'a';
            //cout << "index=" << index << endl;
            //cout << (int)temp << endl;
        
            if(temp > 'z' )
            {
                temp -= alphabetSize;
                //cout << "temp > z " << temp << endl; 
            }
        }
        //cout << (int)temp << endl;
        cipherText += temp;

    }
    return cipherText;
}


// TODO #3
// Implement the decrypt member function according to the given algoirthm.
string VigenereCipher:: decrypt(string ciphertextMsg) const 
{
    string plainText = "";
    char temp;
    for(int i = 0; i < ciphertextMsg.size(); i++)
    {
        temp = ciphertextMsg[i];
        if(temp >= 'a' && temp <= 'z')
        {

            int index = i % key.size();
            temp -= key[index];
            if(temp < 0)
            {
                temp += alphabetSize;
            }
            temp += 'a';
        }
        plainText += temp;
    }
    return plainText;
}


// TODO #4
// Implement the static member function generateRandomKey
// according to the given algorithm.
string VigenereCipher:: generateRandomKey(int length)
{
    string key = "";
    char temp;
    for(int i = 0; i < length; i++)
    {
        temp = _rand() % alphabetSize;
        temp += 'a';
        key += temp;
    }
    return key;
}