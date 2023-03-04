/* Citation and Sources...
Final Project Milestone 3
Module: Publication
Filename: Publication.h
Version 1.0
Author:	Jexequiel Ravni Arador
Date: November 22, 2021
-----------------------------------------------------------
I have done all the coding by myself and only copied the code
that my professor provided to complete my workshops and assignments.
-----------------------------------------------------------*/
#define _CRT_SECURE_NO_WARNINGS
#include "Book.h"
#include "Publication.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

namespace sdds
{

    Book::Book() : Publication()
    {
        m_authorname = nullptr;
    }

    Book::Book(const Book& rhs):Publication(rhs)
    {
       
        if (rhs.m_authorname == nullptr) {
            m_authorname = nullptr;
        }
        else {
            m_authorname = new char[strlen(rhs.m_authorname) + 1];
            strcpy(m_authorname, rhs.m_authorname);
        }
    }

    Book& Book::operator=(const Book& rhs)
    {
        if (this == &rhs) {
            return *this;
        }

        if (this->m_authorname != nullptr) {
            delete[] this->m_authorname;
        }

        Publication::operator=(rhs);

        if (rhs.m_authorname == nullptr) {
            m_authorname = nullptr;
        }
        else {
            m_authorname = new char[strlen(rhs.m_authorname) + 1];
            strcpy(m_authorname, rhs.m_authorname);
        }
        return *this;
    }

    Book::~Book()
    {
        delete[] m_authorname;
        m_authorname = nullptr;
    }

    std::istream& Book::read(std::istream& istr)
    {

        Publication::read(istr);

        if (m_authorname != nullptr);
        delete[] m_authorname;
        char authorname[256];
        if (conIO(istr))
        {
            std::cout << "Author: ";
            istr.ignore();
            istr.getline(authorname, 256, '\n');

        }
        else
        {
            istr.ignore(1);
            istr.getline(authorname, 256);
            
        }

        if (istr.rdstate() == 0)
        {
            m_authorname = new char[strlen(authorname) + 1];
            strcpy(m_authorname, authorname);
        }
        return istr;
    }

    char Book::type() const
    {
        return 'B';
    }

    std::ostream &Book::write(std::ostream &os) const
    {

        Publication::write(os);

        if (Publication::conIO(os))
        {

            if (bool(*this))
            {
                os << " ";

                if (strlen(m_authorname) >= SDDS_AUTHOR_WIDTH) {
                    os.write(m_authorname, SDDS_AUTHOR_WIDTH);
                }
                else {
                    os << std::setw(SDDS_AUTHOR_WIDTH) << std::left << m_authorname;
                }

                os << " |";
            }
        }
        else
        {

            if (bool(*this))
            {
                os << "\t" << m_authorname;
            }
        }

        return os;
    }

    // Modifiers
    void Book::set(int member_id)
    {
        Publication::set(member_id);
        resetDate();
    }

    Book::operator bool() const
    {

        return this->m_authorname != nullptr;
    }

    // RULE OF THREE : Copy Constructor, User Defined Copy Assignment Operator, Destructor

    // HELPER
    std::ostream &operator<<(std::ostream &os, const Book &obj)
    {

        return obj.write(os);
    }

    std::istream &operator>>(std::istream &is, Book &obj)
    {
        return obj.read(is);
    }
};