#include<iostream>
#include<bitset>

int main(){
    std::bitset<32> bitvec(1U);
    bool is_set =bitvec.any();    //true
    bool is_not_set =bitvec.none();   //false
    bool all_set =bitvec.all();        //false

    size_t onBits=bitvec.count();     //returns 1
    size_t sz=bitvec.size();          //returns 32
 
    bitvec.flip();
    bitvec.reset();           //全部位重置为0
    bitvec.set();             //全部位重置为1


}



