
#ifndef ACCOUNT_H
#define ACCOUNT_H

#include <string>

typedef double Money;   //给double去个别名，钱

std::string bal;

class Account {
    public:
        Money balance() {
            return bal;
        }
    
    private:
        Money bal;
};

#endif