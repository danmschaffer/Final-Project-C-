#define _CRT_SECURE_NO_WARNINGS
#include "LibApp.h"
#include<iostream>
#include<cstring>
#include<iomanip>
#include<fstream>
#include <string.h>

namespace sdds {

      bool LibApp::confirm(const char* message)
      {
         Menu conf(message);
         conf<<"Yes";

         int t_return = conf.run();

         if(t_return) return true;

          return false;

      }

      void LibApp::load(){
          std::cout<<"Loading Data\n";
          std::fstream readF;
          readF.open(m_file_name, std::ios::in);
          if (readF.is_open() == false)
              return;
          Publication* current_pub = nullptr;
          while (readF.rdstate() == std::ios::goodbit) {
              char publication_type;
              readF.get(publication_type);
              readF.ignore();

              if (publication_type == 'P') {
                  current_pub = new Publication();
              }
              else
                  current_pub = new Book();

              readF >> (*current_pub);
                
              if (readF.rdstate() == std::ios::goodbit) {
                  m_pub_arr[m_loaded_num] = current_pub;
                  m_loaded_num++;
                 if (publication_type == 'P')
                     readF.ignore();
              }
          }
          if (current_pub != nullptr) {
              m_lastLib_ref = m_pub_arr[m_loaded_num-1]->getRef();
              delete current_pub;
          }
      
      } 
      void LibApp::save(){
          std::cout<<"Saving Data\n";
          std::fstream writeF;
          writeF.open(m_file_name, std::ios::out);
          if (writeF.is_open() == false)
              return;
          
          for (int i = 0; i < m_loaded_num; i++) {
              if (m_pub_arr[i]->getRef() != 0)
                  writeF << (*m_pub_arr[i]) << std::endl;
          }
      }
      int LibApp::search(const int all, const int checkedOut, const int availble)
      {
          char pub_type;
          int option = m_typeMenu.run();
          std::cin.ignore();
          if (option == 1)
              pub_type = 'B';
          else if (option == 2)
              pub_type = 'P';
          else
          {
              std::cout << "Aborted!" << std::endl;
              return 0;
          }

          char search_title[256] = "";
          std::cout << "Publication Title: ";
          std::cin.getline(search_title, 256);

          PublicationSelector pub_selector("Select one of the following found matches:");
          for (int i = 0; i < m_loaded_num; i++) {
              if (m_pub_arr[i]->getRef() != 0 && m_pub_arr[i]->type() == pub_type && 
                  std::strstr((*m_pub_arr[i]),search_title) ) {
                  
                  if (all == 1) {
                      pub_selector << m_pub_arr[i];
                  }
                  else if (checkedOut == 1 && m_pub_arr[i]->onLoan() == true) {
                      pub_selector << m_pub_arr[i];
                  }
                  else if (availble == 1 && m_pub_arr[i]->onLoan() == false) {
                      pub_selector << m_pub_arr[i];
                  }
              }
          }

          if (pub_selector) {
              pub_selector.sort();
              option = pub_selector.run();
              if (option != 0) {
                  Publication* pub_ptr = getPub(option);
                  std::cout << (*pub_ptr) << std::endl;
              }
              else
                  std::cout << "Aborted!" << std::endl;
              return option;
          }

          else
              std::cout << "No matches found!" << std::endl;
          return 0;
      }
      
      
      void LibApp::returnPub()  
      {
          std::cout << "Return publication to the library" << std::endl;
          int s_ref = search(0, 1, 0);
          if (s_ref && confirm("Return Publication?")) {
              Publication* pub_ptr = getPub(s_ref);
              
              if ((Date() - pub_ptr->checkoutDate()) > 15) {
                  std::cout << std::setprecision(2) << std::fixed;
                  std::cout << "Please pay $";
                  std::cout << (Date() - pub_ptr->checkoutDate() - 15) / 2.0;
                  std::cout << " penalty for being ";
                  std::cout << (Date() - pub_ptr->checkoutDate() - 15) << " days late!\n";
              }

              pub_ptr->set(0);
              m_changed = true;
              std::cout << "Publication returned\n";
          }
          else if (s_ref != 0) {
              std::cout << "Aborted!" << std::endl;
          }
          
              
         
         

      }

      void LibApp::newPublication()
      {

          if (m_loaded_num == SDDS_LIBRARY_CAPACITY) {
              std::cout << "Library is at its maximum capacity!\n";
              return;
          }
         std::cout<<"Adding new publication to the library\n";

         int option = m_typeMenu.run();
         std::cin.ignore();

         Publication* current_pub;
         if (option == 1)
             current_pub = new Book();
         else if (option == 2)
             current_pub = new Publication();
         else
         {
             std::cout << "Aborted!" << std::endl;
             return;
         }

         std::cin >> (*current_pub);
         if (std::cin.rdstate() == std::ios::badbit) {
             std::cin.ignore(1000, '\n');
             std::cout << "Aborted!" << std::endl;
             delete current_pub;
             return;
         }

         if(confirm("Add this publication to the library?"))
         {
             if (current_pub) {
                 
                 m_lastLib_ref++;
                 current_pub->setRef(m_lastLib_ref);
                 m_pub_arr[m_loaded_num] = current_pub;
                 m_loaded_num++;
                 m_changed = true;
                 std::cout << "Publication added\n";
             }
             else
             {
                 std::cout << "Failed to add publication!\n";
                 delete current_pub;
             }
         }
         else {

             delete current_pub;
             std::cout << "Aborted!" << std::endl;
         }
             
      }

      void LibApp::removePublication()
      {
         //std::cout<<;

         std::cout<<"Removing publication from the library\n";

         int s_ref = search(1,0,0);
         if (s_ref != 0 && confirm("Remove this publication from the library?")) {
             Publication* pub_ptr = getPub(s_ref);
             pub_ptr->setRef(0);
             m_changed = true;
             std::cout << "Publication removed\n";
         }
         else if(s_ref != 0)
             std::cout << "Aborted!" << std::endl;
  
      }

      void LibApp::checkOutPub()
      {
          std::cout << "Checkout publication from the library" << std::endl;
         int s_ref = search(0,0,1);
         
         if(s_ref  != 0 && confirm("Check out publication?"))
         {
             int pub_num;
             std::cout << "Enter Membership number: ";
             std::cin >> pub_num;
             while (std::cin.rdstate() == std::ios::badbit || pub_num < 10000 || pub_num > 99999)
             {  
                 std::cin.ignore(1000, '\n');
                 std::cin.clear();
                 std::cout << "Invalid membership number, try again: ";
                 std::cin >> pub_num;
             }

             Publication* pub_ptr = getPub(s_ref);
             pub_ptr->set(pub_num);
             m_changed = true;
             std::cout<<"Publication checked out\n";
         }
         else if(s_ref != 0)
             std::cout << "Aborted!" << std::endl;


      }

      Publication* LibApp::getPub(int libRef)
      {
          for (int i = 0; i < m_loaded_num; i++) {
              if (m_pub_arr[i]->getRef() == libRef)
                  return m_pub_arr[i];
          }

          return nullptr;
      }



      LibApp::LibApp(const char* file)
      {
         strcpy(m_file_name, file);
         m_loaded_num = 0;
         m_mainMenu << "Add New Publication" 
         << "Remove Publication" 
         << "Checkout publication from library"
         <<"Return publication to library";

         m_exitMenu << "Save changes and exit" << "Cancel and go back to the main menu";

         m_typeMenu << "Book" << "Publication";

         load();

      }


      

      void LibApp::run()
      {
         while(1)
         {  
            int option =  m_mainMenu.run();

            if( option == 1 )
            {
               newPublication();
            }
            else if( option == 2 ) 
            {
               removePublication();
            }
            else if( option == 3 )
            {
               checkOutPub();
            }
            else if( option == 4 )
            {
               returnPub();
            }
            else if( option == 0 )
            {
               if(m_changed)
               {
                  
                  int opn = m_exitMenu.run();

                  if( opn == 1 )
                  {
                     save();
                     break;
                  }
                  else if( opn == 2 )
                  {
                     ;
                  }
                  else if( opn == 0)
                  {  
                     if(confirm("This will discard all the changes are you sure?"))
                        break;
                  }

               }
               else break;


            }

            std::cout<<std::endl;

            
         }



         std::cout<<std::endl;
         std::cout<<"-------------------------------------------\n";
         std::cout<<"Thanks for using Seneca Library Application\n";

      }

      LibApp::~LibApp()
      {
          int deleted = 0;
          while (deleted < m_loaded_num) {
              delete m_pub_arr[deleted];
              m_pub_arr[deleted] = nullptr;
              deleted++;
          }
      }


         

}