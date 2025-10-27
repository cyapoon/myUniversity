#include"filter.h"

FilterModule:: ~FilterModule()
{
    
}

void FilterModule:: print() const
{
    std::cout << "Module name = " << m_name << ", this is a filter, filter type = " << getFilterType(type) << std::endl;
}

void FilterModule:: trainPreData(const string &source, const string &target)
{
    //if(this->preData.find(source) == "")
    {
        this->preData.insert(source, target);
    }
}

void FilterModule:: trainPostData(const string &source, const string &target)
{
    //if(this->postData.find(source) == "")
    {
        this->postData.insert(source, target);
    }
}

string FilterModule:: translatePreData(string question) const
{
    string result = this->preData.find(question);
    if(result != "")
    {
        return result;
    }
    else
    {
        return question;
    }
}

string FilterModule:: translatePostData(string question) const
{
    string result = this->postData.find(question);
    if(result != "")
    {
        return result;
    }
    else
    {
        return question;
    }
}

//FilterArray

void FilterArray:: insert(FilterModule *input)
{
    if(this->arraySize == 0)
    {
        this->arraySize++;
        this->array = new FilterModule*[this->arraySize];
        this->array[0] = input;
        return;
    }
    else
    {
        FilterModule** temp_array = new FilterModule*[this->arraySize + 1];
        for(int i = 0; i < this->arraySize; i++)
        {
            temp_array[i] = this->array[i];
        }
        temp_array[this->arraySize] = input;
        delete [] this->array;
        this->array = temp_array;
        this->arraySize++;
        return;
    }
}

FilterModule *FilterArray:: get(int index) const
{
    if(index >= 0 && index < this->arraySize)
    {
        return this->array[index];
    }
    else
    {
        return nullptr;
    }
}