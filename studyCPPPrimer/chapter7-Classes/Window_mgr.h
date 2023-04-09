#ifndef WINDOW_MGR
#define WINDOW_MGR

#include <vector>
#include <string>
#include <iostream>
#include "Screen.h"
//Window_mgr类的声明
class Window_mgr{

    public:

        using ScreenIndex = std::vector<Screen>::size_type;

        void clear(ScreenIndex);

        ScreenIndex addScreen(const Screen&);

    private:
        std::vector<Screen> screens{Screen(24, 80, ' ')};
};

void Window_mgr::clear(ScreenIndex i)
{
    Screen &s=screens[i]; //s是一个引用，是Screen想要清扫的

    s.contents=std::string(s.height * s.width, ' ');

}

Window_mgr::ScreenIndex
Window_mgr::addScreen(const Screen & s)
{
    screens.push_back(s);    //screens 是一个Screen类型的容器
    return screens.size() -1;
}

#endif