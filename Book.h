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
#ifndef SDDS_BOOK_H
#define SDDS_BOOK_H
#include "Publication.h"
#include <iostream>
#include <iomanip>
#include <string>
#include <cstring>

namespace sdds {
	class Book : public Publication{
		char* m_authorname{};
		
	public:

		Book();

		Book(const Book& rhs);
		Book& operator = (const Book& rhs);
		~Book();


		

		bool conIO(std::ios& ios) const {
			// This method is not capable of modifying the Streamable object. conIo receives a reference of an ios object and returns a Boolean.
			// Functions overriding this function will determine if the incoming ios object is a console IO object or not.
			return &ios == &std::cin || &ios == &std::cout;
		}

		virtual std::istream &read(std::istream &istr);

		virtual char type()const;

		virtual std::ostream& write(std::ostream& os) const;

        // Modifiers
        virtual void set(int member_id);

        virtual operator bool() const;

	};

	std::ostream& operator<<(std::ostream& os, const Book& obj);

	std::istream& operator>>(std::istream& is, Book& obj);

	
}

#endif