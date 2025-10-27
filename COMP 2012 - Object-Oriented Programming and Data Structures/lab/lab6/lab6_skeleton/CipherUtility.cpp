#include "CipherUtility.h"

// TODO #5
// Implement the static member function isKeyValid
bool CipherUtility:: isKeyValid(const Cipher* cipher)
{
    bool temp;
    for(int i = 0; i < cipher->key.size(); i++)
    {
        temp = isalpha(cipher->key[i]);
        if(temp == 0)
        {
            return false;
        }
    }
    return true;
}

// TODO #6
// Implement the static member function removeNonAlphaCharsHelper
string CipherUtility:: removeNonAlphaCharsHelper(string str)
{
    string result = "";
    string substring = "";
    for(int i = 1; i < str.size(); i++)
    {
        substring += str[i];
    }
    if(str == "")
    {
        return "";
    }
    else
    {
        char c = str[0];
        if(isalpha(c))
        {
            result += c;
            return (result += removeNonAlphaCharsHelper(substring));
        }
        else
        {
            return (result += removeNonAlphaCharsHelper(substring));
        }
    }
}