
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

        void calculate(){
            amount+= amount  * interestRate;

        }

        static double rate(){
            return interestRate;
        }

        static void rate(double);
    
    private:
        Money bal;

        std::string owner;
        double amount;
        static double interestRate;
        static double initRate();
};

#endif