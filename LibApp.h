#ifndef SDDS_LIBAPP_H
#define SDDS_LIBAPP_H
#include "Menu.h"
#include "Lib.h"
#include "Publication.h"
#include "Book.h"
#include "PublicationSelector.h"

namespace sdds {
   class LibApp {
      
      bool m_changed=false;
      Menu m_mainMenu{"Seneca Library Application"};
      Menu m_exitMenu{"Changes have been made to the data, what would you like to do?"};
      Menu m_typeMenu{"Choose the type of publication:"};

      Publication* m_pub_arr[SDDS_LIBRARY_CAPACITY];
      char m_file_name[256];
      int m_loaded_num;
      int m_lastLib_ref;

      bool confirm(const char* message);
      void load();  // prints: "Loading Data"<NEWLINE>
      void save();   // prints: "Saving Data"<NEWLINE>
      
      int search(const int all = 0, const int checkedOut = 0,const int availble = 0);
      
      void returnPub();  

      void newPublication();

      void removePublication();

      void checkOutPub();

      Publication* getPub(int libRef);

      

      public:

      LibApp(const char*);

      void run();

      ~LibApp();
   };
}
#endif // !SDDS_LIBAPP_H