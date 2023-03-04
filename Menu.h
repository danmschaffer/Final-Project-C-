 // Final Project Milestone 1 
// Date Module
// File	Date.h
// Version 1.0
// Author	Fardad Soleimanloo
// Revision History
// -----------------------------------------------------------
// Name               Date                 Reason
// Fardad             2021/10/29	       Preliminary release
/////////////////////////////////////////////////////////////////
#ifndef SDDS_MENU_H
#define SDDS_MENU_H
#include <iostream>
namespace sdds {
    int const MAX_MENU_ITEMS = 20;
    class Menu;
    class MenuItem{
            char* m_menuItem{}; 
            MenuItem();
            MenuItem(const char* item );
            ~MenuItem();
            operator bool() const;
            void display();
            friend Menu;
    };

    class Menu {
            char* m_menuTitle{}; 
            MenuItem* m_items[MAX_MENU_ITEMS];
            int m_noofmenu=0;
        public:
            Menu();
            Menu(const char* title);
            ~Menu();
            int run();
            char* operator[](int i) const;
            operator bool() const;
            int operator~();
            void display();
            std::ostream& write(std::ostream& os = std::cout)const;
            Menu& operator<<(const char* menuitemConent);
            // operator int() const;
            operator unsigned int() const;
    };

    std::ostream& operator<<(std::ostream& os, const Menu& m);

}
#endif