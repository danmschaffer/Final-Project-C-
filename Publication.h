#ifndef SDDS_PUBLICATION_H__
#define SDDS_PUBLICATION_H__
#include <iostream>
#include "Lib.h"
#include "Date.h"
#include <stdio.h>
#include <cstring>
#include "Streamable.h"

namespace sdds {

    const int m_MAXTITLE = 255;
    const int m_MAXSHELFID = 4;

    class Publication:public Streamable {

        char* m_title{};
        char* m_shelfId{};
        int m_membership=0;
        int m_libRef=-1;
        Date m_date;

        public:
	

        Publication();

        Publication(const Publication& rhs);
        Publication& operator = (const Publication& rhs);
        virtual ~Publication();

        virtual void set(int member_id);


        void setRef(int value);
        
        void resetDate();


        virtual char type()const ;
        
        bool onLoan()const;
    
        

        Date checkoutDate()const;

        bool operator==(const char* title)const;
        
        operator const char* ()const;

        int getRef()const;


        bool conIO(std::ios& io)const;
        

        std::ostream& write(std::ostream& os) const;
        std::istream& read(std::istream& istr);


        operator bool() const;


    };


    /*std::ostream& operator<<(std::ostream& os, const Publication& PO);
    std::istream& operator>>(std::istream& is, Publication& PI);*/

}
#endif