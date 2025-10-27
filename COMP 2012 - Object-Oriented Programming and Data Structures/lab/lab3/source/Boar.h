#ifndef BOAR_H
#define BOAR_H

#include "Animal.h"

//  TODO: Complete the class declaration of Boar
class Boar : public Animal
{
    private:
        std::string location;

    public:
        Boar(const std::string&, const std::string&);
        std::string get_location() const;
        void go_to(const std::string&);
        void bite_package() const;
        ~Boar();
};


#endif