#include "Sales_data.h"
#include "Screen.h"

int main()
{
    Screen myScreen(5,3);
    
    const Screen blank(5,3);

    myScreen.set('#');
    myScreen.display(std::cout);

    blank.display(std::cout);


    return 0;

}
