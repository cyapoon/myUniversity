#include"handler.h"

HandlerModule:: ~HandlerModule()
{
    if(this->languageFilter != nullptr)
    {
        this->languageFilter = nullptr;
    }

    if(this->toneFilter != nullptr)
    {
        this->toneFilter = nullptr;
    }
}
    
void HandlerModule:: print() const
{
    std::cout << "Module name = " << m_name << ", this is a Handler, can handle topic = " << topic << std::endl;
}

void HandlerModule:: trainData(const string &question, const string &answer)
{
    this->data.insert(question,answer);
}
    
string HandlerModule:: answer(const string &question) const
{
    string temp_question = question;
    
    if(this->languageFilter != nullptr)
    {
        temp_question = this->languageFilter->translatePreData(temp_question);
    }

    if(this->toneFilter != nullptr)
    {
        temp_question = this->toneFilter->translatePreData(temp_question);
    }

    string answer = this->inneranswer(temp_question);

    if(this->toneFilter != nullptr)
    {
        answer = this->toneFilter->translatePostData(answer);
    }

    if(this->languageFilter != nullptr)
    {
        answer = this->languageFilter->translatePostData(answer);
    }

    return answer;

}

 string HandlerModule:: inneranswer(const string &question) const
 {
    string temp = this->data.find(question);
    if(temp != "")
    {return temp;}
    else
    {return "Sorry, I don't know";}
    
 }


//implement of HandlerMap
 HandlerMap:: HandlerMap()
 {
    this->arraySize = 0;
    this->names = nullptr;
    handlerModules = nullptr;
 }

HandlerMap:: ~HandlerMap() {clear();}

void HandlerMap:: insert(string key, HandlerModule *value)
{
    if(this->arraySize == 0)
    {
        this->arraySize++;
        this->names = new string[this->arraySize];
        this->names[0] = key;
        this->handlerModules = new HandlerModule*[this->arraySize];
        this->handlerModules[0] = value;
        return;
    }
    else
    {
        string* temp_names = new string[this->arraySize + 1];
        HandlerModule** temp_handlerModules = new HandlerModule*[this->arraySize + 1];
        for(int i = 0; i < this->arraySize; i++)
        {
            temp_names[i] = this->names[i];
            temp_handlerModules[i] = this->handlerModules[i];
        }
        temp_names[this->arraySize] = key;
        temp_handlerModules[this->arraySize] = value;
        delete [] this->names;
        this->names = temp_names;
        delete [] this->handlerModules;
        this->handlerModules = temp_handlerModules;
        this->arraySize++;
        return;
    }
}
    
HandlerModule * HandlerMap:: find(const string &key) const
{
    for(int i = 0; i < this->arraySize; i++)
    {
        if(this->names[i] == key)
        {
            return this->handlerModules[i];
        }
    }

    return nullptr;
}
    
string HandlerMap:: getNames(int index) const
{
    if(index >= 0 && index < (this->arraySize))
    {
        return this->names[index];
    }
    else
    {
        return nullptr;
    }
}
    
void HandlerMap:: clear()
{
    if(this->names != nullptr)
    {
        delete [] this->names;
        this->names = nullptr;
    }
    if(this->handlerModules != nullptr)
    {
        delete [] this->handlerModules;
        this->handlerModules = nullptr;
    }
    this->arraySize = 0;
    
}