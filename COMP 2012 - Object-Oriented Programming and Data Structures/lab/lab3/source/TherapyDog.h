#ifndef THERAPYDOG_H
#define THERAPYDOG_H

#include "Dog.h"

//  TODO: Complete the class declaration of TherapyDog
class TherapyDog :public Dog
{
    private:
        std::string employment;

    public:
        TherapyDog(const std::string &, const std::string&, const std::string&);
        std::string get_employment() const;
        void smile() const;

};

#endif