#include<iostream>
#include<bitset>
// int main(){

//     std::bitset<16> bits;

//     std::cin >> bits;
//     std::cout<< "bits: "<<bits<<std::endl;
// }

int main(){

    bool status;

    unsigned long quizA=0;

    quizA |=1UL<<27;
    status = quizA& (1UL<<27);
    quizA &= ~(1UL<<27);

    std::bitset<30> quizB;
    quizB.set(27);
    status= quizB[27];
    quizB.reset(27);
    }