#define  _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Menu.h"
#include <iomanip>
using namespace std;
namespace sdds {

    MenuItem::MenuItem()
    {
        m_menuItem = nullptr;
    }

    MenuItem::MenuItem(const char* item )
    {   
        delete[] m_menuItem;
		m_menuItem = new char[strlen(item) + 1];
		strcpy(m_menuItem, item);
    }


    MenuItem::~MenuItem()
    {
        delete[] m_menuItem;
    }

    MenuItem::operator bool() const{
        
        if( m_menuItem != nullptr ) return true;

        return false;
    }

    
    void MenuItem::display(){
        std::cout << m_menuItem;
    }


    Menu::Menu()
    {
        m_menuTitle = nullptr;
        m_noofmenu = 0;
    }

    Menu::Menu(const char* title)
    {
        delete[] m_menuTitle;
		m_menuTitle = new char[strlen(title) + 1];
		strcpy(m_menuTitle, title);
    }


    Menu::~Menu()
    {
        delete[] m_menuTitle;
        for (int i = 0; i < m_noofmenu; i++) delete m_items[i];
    }


    void Menu::display()
    {
        if(m_menuTitle != nullptr) 
            cout<<m_menuTitle<<"\n";

        for(int i=0; i<m_noofmenu ; i++ )
            cout<<" " << i + 1 << "- " << m_items[i]->m_menuItem << endl;
        
        cout<<" 0- Exit\n> ";

    }
    
    int Menu::run()
    {   

        display();
        char op;
        cin>>op;
        int o = op -'0';
        while ( o  < 0 || o > m_noofmenu  )
        {   

            cin.clear(); //clear bad input flag
            cin.ignore(80, '\n');
            cout<<"Invalid Selection, try again: ";
            cin>>op;
            o = op -'0';
        }
        
        return o;
        
    }

    Menu::operator bool() const
    {   
        if(m_menuTitle==nullptr) return false;
        return true; 
    }

    int Menu::operator~()
    {
        display();
        char op;
        cin>>op;

        int o = op -'0';
        while ( o  < 0 || o > m_noofmenu  )
        {   

            cin.clear(); //clear bad input flag
            cin.ignore(80, '\n');
            cout<<"Invalid Selection, try again: ";
            cin>>op;
            o = op -'0';
        }
        
        return o;
    }

    Menu& Menu::operator<<(const char* menuitemConent)
    {   
        m_items[m_noofmenu++] = new MenuItem(menuitemConent);
        return *this;
    }

    

    // Menu::operator int() const { return m_noofmenu; }



    std::ostream& Menu::write(std::ostream& os )const
    {   
        if( m_menuTitle != nullptr )
            os<<m_menuTitle;
        return os;
    }

    std::ostream& operator<<(std::ostream& os, const Menu& m)
    {   
        return m.write(os);
    }

    Menu::operator unsigned int() const { return m_noofmenu; }

    char* Menu::operator[](int i) const
    {
        return m_items[i]->m_menuItem;
    }

}