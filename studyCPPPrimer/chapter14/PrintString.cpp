#include<iostream>
#include"PrintString.h"
#include"SizeComp.h"
int main()
{
    PrintString printer;
    printer(s);
    PrintString errors(std::cerr, '\n');
    errors(s);
    return 0;
}