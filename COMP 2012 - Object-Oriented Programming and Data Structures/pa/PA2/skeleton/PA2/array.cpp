#include"array.h"

DataMap::DataMap()
{
    //std:: cout << "DataMap's constructor called" << endl;
    this->arraySize = 0;
    this->keys = nullptr;
    this->values = nullptr;
}

DataMap::~DataMap()
{
    //std::cout << "DataMap's destructor called" << endl;
    clear();
}


void DataMap :: insert(const string &key, const string &value)
{
    if(this->arraySize == 0)
    {
        this->arraySize++;
        this->keys = new string[this->arraySize];
        this->keys[0] = key;
        this->values = new string[this->arraySize];
        this->values[0] = value;
        return;
    }
    else
    {
        string* temp_keys = new string[this->arraySize + 1];
        string* temp_values = new string[this->arraySize +1];
        for(int i = 0; i < this->arraySize;i++)
        {
            temp_keys[i] = this->keys[i];
            temp_values[i] = this->values[i];
        }
        temp_keys[this->arraySize] = key;
        temp_values[this->arraySize] = value;
        delete [] this->keys;
        delete[] this->values;
        this->keys = temp_keys;
        this->values = temp_values;
        this->arraySize++;
        return;
    }

}

string DataMap :: find(const string &key) const
{
    for(int i = 0; i < this->arraySize;i++)
    {
        if(this->keys[i] == key)
        {
            return this->values[i];
        }
    }
    return "";
}


void DataMap:: clear()
{
    this->arraySize = 0;
    if(this->keys != nullptr)
    {
        delete [] this->keys;
        this->keys = nullptr;
    }
    if(this->values != nullptr)
    {
        delete [] this->values;
        this->values = nullptr;
    }
}
