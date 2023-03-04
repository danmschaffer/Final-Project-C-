#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <cstring>
#include "Publication.h"
#include "Book.h"
#include <iomanip>
using namespace std;
namespace sdds
{

    Publication::Publication()
    {
        m_title = nullptr;
        m_shelfId = nullptr;
        m_membership = 0;
        m_libRef = -1;
    }

    Publication::Publication(const Publication &rhs)
    {
        if (rhs.m_title == nullptr)
            this->m_title = nullptr;
        else
        {
            this->m_title = new char[strlen(rhs.m_title) + 1];
            strcpy(this->m_title, rhs.m_title);
        }
        if (rhs.m_shelfId == nullptr)
            this->m_shelfId = nullptr;
        else
        {
            this->m_shelfId = new char[strlen(rhs.m_shelfId) + 1];
            strcpy(this->m_shelfId, rhs.m_shelfId);
        }

        this->m_date = rhs.m_date;
        this->m_libRef = rhs.m_libRef;
        this->m_membership = rhs.m_membership;
    }

    Publication &Publication::operator=(const Publication &rhs)
    {
        if (this == &rhs)
            return *this;

        if (this->m_title != nullptr)
        {
            delete[] this->m_title;
            this->m_title = nullptr;
        }

        if (this->m_shelfId != nullptr)
        {
            delete[] this->m_shelfId;
            this->m_shelfId = nullptr;
        }

        if (rhs.m_title == nullptr)
            this->m_title = nullptr;
        else
        {
            this->m_title = new char[strlen(rhs.m_title) + 1];
            strcpy(this->m_title, rhs.m_title);
        }
        if (rhs.m_shelfId == nullptr)
            this->m_shelfId = nullptr;
        else
        {
            this->m_shelfId = new char[strlen(rhs.m_shelfId) + 1];
            strcpy(this->m_shelfId, rhs.m_shelfId);
        }

        this->m_date = rhs.m_date;
        this->m_libRef = rhs.m_libRef;
        this->m_membership = rhs.m_membership;

        return *this;
    }

    Publication::~Publication()
    {
        delete[] this->m_title;
        delete[] this->m_shelfId;
    }

    void Publication::set(int member_id)
    // Sets the membership attribute to either zero or a five-digit integer.
    {
        m_membership = member_id;
    }

    void Publication::setRef(int value)
    // Sets the **libRef** attribute value
    {
        m_libRef = value;
    }

    void Publication::resetDate()
    // Sets the date to the current date of the system.
    {
        m_date.setToToday();
    }

    char Publication::type() const { return 'P'; }
    // Returns the character 'P' to identify this object as a "Publication object"

    bool Publication::onLoan() const
    {
        if (m_membership != 0)
            return true;

        return false;
    }
    // Returns true is the publication is checkout (membership is non-zero)

    Date Publication::checkoutDate() const
    {
        return m_date;
    }
    // Returns the date attribute

    bool Publication::operator==(const char *title) const
    {
        if (strstr(m_title, title))
            return true;
        return false;
    }
    // Returns true if the argument title appears anywhere in the title of the
    // publication. Otherwise, it returns false; (use strstr() function in <cstring>)

    Publication::operator const char *() const
    // Returns the title attribute
    {
        return m_title;
    }

    int Publication::getRef() const
    // Returns the libRef attirbute.
    {
        return m_libRef;
    }

    bool Publication::conIO(std::ios &io) const
    {
        return &io == &std::cin || &io == &std::cout;
    }

    std::ostream &Publication::write(std::ostream &os) const
    {

        // std::cout<<m_shelfId<<m_title;

        if (checkoutDate() && m_shelfId != nullptr && m_title != nullptr && m_title[0] != '\n' && m_shelfId[0] != '\n')
        {
            if (conIO(os))
            {
                os << "| " << m_shelfId << " | ";

                if (strlen(m_title) >= SDDS_TITLE_WIDTH) {
                    os.write(m_title, SDDS_TITLE_WIDTH);
                }

                else {
                    os << m_title;
                    os.width(30 - strlen(m_title) + 3);
                    os.fill('.');
                }
                

                os << right << " | ";

                if (m_membership == 0)
                    os << " N/A ";
                else
                    os << m_membership;

                os << " | " << m_date << " |";
            }
            else
            {

                os << type() << "\t" << m_libRef << "\t" << m_shelfId << "\t" << m_title << "\t" << m_membership << "\t" << m_date;
            }
        }

        return os;
    }

    std::istream &Publication::read(std::istream &istr)
    {
        delete[] m_title;
        delete[] m_shelfId;
        m_shelfId = nullptr;
        m_title = nullptr;
        m_membership = 0;
        m_libRef = -1;
        resetDate();
        char shelfId[256];
        char title[256];

        if (conIO(istr))
        {

            std::cout << "Shelf No: ";
            istr >> shelfId;
            if (strlen(shelfId) != 4)
            {
                
                istr.setstate(ios::failbit);
                istr.setstate(ios::badbit);
                std::cout << "Title: ";
                std::cout << "Date: ";
                return istr;
            }
            else
                istr.ignore();

            m_shelfId = new char[strlen(shelfId) + 1];
            strcpy(m_shelfId, shelfId);

            std::cout << "Title: ";
            istr.getline(title, 255,'\n');
            m_title = new char[strlen(title) + 1];
            strcpy(m_title, title);

            std::cout << "Date: ";
            istr >> m_date;
        }
        else
        {

            char c[6];
            istr.getline(c, 6, '\t');
            m_libRef = atoi(c);

            istr.getline(shelfId, SDDS_SHELF_ID_LEN + 1, '\t');
            m_shelfId = new char[strlen(shelfId) + 1];
            strcpy(m_shelfId, shelfId);

            istr.getline(title, 255, '\t');

            m_title = new char[strlen(title) + 1];

            strcpy(m_title, title);

            istr >> m_membership;

            istr >> m_date;
           
        }

        if (m_date.errCode() != 0)
        {
            istr.setstate(std::ios::failbit);
            delete[] m_title;
            delete[] m_shelfId;
            m_shelfId = nullptr;
            m_title = nullptr;
            m_membership = 0;
            m_libRef = -1;
            resetDate();
            return istr;
        }

        return istr;
    }

    Publication::operator bool() const
    {
        if (m_shelfId != nullptr && m_title != nullptr && m_title[0] != '\n' && m_shelfId[0] != '\n')
            return true;

        return false;
    }

    std::ostream &operator<<(std::ostream &os, const Publication &PO)
    {
        return PO.write(os);
    }
    std::istream &operator>>(std::istream &is, Publication &PI)
    {
        return PI.read(is);
    }

};