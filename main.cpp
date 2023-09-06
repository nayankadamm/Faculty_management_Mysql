#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include <cppconn/prepared_statement.h>
#include <iostream>
#include <stdlib.h>
#include "headerfiles/admin.h"
#include "headerfiles/faculty.h"
#include "DatabaseConnection/DatabaseConnector.h"
using namespace std;
int main()
{
    DatabaseConnector dbConnector("tcp://127.0.0.1:3306", "root", "", "project");
    dbConnector.connect();
    admin loginManager(&dbConnector);
    faculty flogin(&dbConnector);
   //dbConnector.disconnect();
    int ch;
    cout<<""<<endl;
    cout<<""<<endl;
    cout<<"\t\t\t\t "<<"********* WELCOME TO HOME PAGE **********"<<endl;
    cout<<""<<endl;
    cout<<"\t\t\t\t 1:ADMIN"<<endl;
    cout<<"\t\t\t\t 2:FACULTY"<<endl;
    cout<<"\t\t\t\t 3:Quit"<<endl;
    cout<<""<<endl;
    cout<<"\t\t\t\t"; cin>>ch;
    switch (ch)
    {
        case 1:
                            
                cout<<"\t\t\t\t ************ WELCOME TO ADMIN LOGIN PAGE ************"<<endl;
                
             
                loginManager.startLogin(); //admin login function
                
               break;
        case 2:
            
                flogin.startLogin();
            
            
        break;
         case 3:
                break;
        default:
            cout<<"\t\t\t\t Invalid Choice !!!!!!"<<endl;
            main();
            break;
    }

    return 0;
}