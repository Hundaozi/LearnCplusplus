#ifndef WINDOW_MGR
#define WINDOW_MGR

#include <vector>
#include <string>
#include <iostream>
#include "Screen.h"
//Window_mgr类的声明
class Window_mgr{

    private:
        std::vector<Screen> screens{Screen(24, 80, ' ')};
};

#endif