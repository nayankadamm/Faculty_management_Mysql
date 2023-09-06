#include<iostream>
#include<fstream>
#include<ostream>
#include<istream>
#include<stdlib.h>
#include<vector>
#include<sstream>
#include<map>
#include "../headerfiles/faculty.h"
#include <cppconn/statement.h>
#include<cppconn/prepared_statement.h>
using namespace std;
faculty::faculty(DatabaseConnector* connector) : dbConnector(connector) {}
string fname;
void faculty::startLogin() {
    // Prompt user for name and password
    std::string name, password;
    std::cout << "Enter name: ";
    std::cin >> name;
    std::cout << "Enter password: ";
    std::cin >> password;
    fname=name;
    // Perform login
    bool loggedIn = performLogin(name, password);
    // Continue with the program based on login status
    if (loggedIn) {
        //cout<<"logged in"<<endl;
      faculty_work();
    } else {
        std::cout << "Invalid name or password. Login failed." << std::endl;
        startLogin();
    }
}

bool faculty::performLogin(const std::string& name, const std::string& password) {
    // Query to check if name and password match
    std::string query = "SELECT COUNT(*) FROM faculty WHERE name = '" + name + "' AND password = '" + password + "'";

    sql::Statement *stmt;
    stmt = dbConnector->getConnection()->createStatement();
    sql::ResultSet *res = stmt->executeQuery(query);

    if (res->next()) {
        int count = res->getInt(1);
         
        delete res;
        delete stmt;
        if (count > 0) {
            std::cout << "Login successful!" << std::endl;
            return true;
        }
        else{
            return false;
        }
    }

    delete res;
    delete stmt;
   
}
    void faculty:: faculty_work()
    {
        int ch;
        cout<<"Welcome to Faculty Dashboard"<<endl;
        cout<<"1:Get schedule"<<endl;
        cout<<"2:accept/reject schedule"<<endl;
        cout<<"3:exit"<<endl;
        cout<<"enter the choice::";
        cin>>ch;
        switch (ch)
        {
        case 1:
                get_shedule();
            break;
            case 2:
                cancle_shedule();
            break;
            
        
        default:
            break;
        }
    }  
    void faculty:: get_shedule()
{
     std::string query = "select * from allocated_schedules where faculty_name ='"+fname+"' ";
sql::Statement *stmt;
    stmt = dbConnector->getConnection()->createStatement();
    sql::ResultSet *res = stmt->executeQuery(query);
    
     sql::ResultSetMetaData *metaData = res->getMetaData();
        int columnCount = metaData->getColumnCount();
        std::vector<std::string> columnNames;

        for (int i = 1; i <= columnCount; i++) {
            columnNames.push_back(metaData->getColumnName(i));
        }

        // Print the retrieved data
        int nameWidth = 15;  // Adjust the width as per your needs
        std::cout << std::left;

        // Print the column headers
        for (const std::string& columnName : columnNames) {
            std::cout << std::setw(nameWidth) << columnName << " ";
        }
        std::cout << std::endl;

        // Print the data rows
        while (res->next()) {
            for (const std::string& columnName : columnNames) {
                std::string columnValue = res->getString(columnName);
                std::cout << std::setw(nameWidth) << columnValue << " ";
            }
            std::cout << std::endl;
        }


}
int faculty:: cancle_shedule()
{           
    bool updatefalse = false;
   std::string query = "select * from allocated_schedules where faculty_name ='"+fname+"' ";
sql::Statement *stmt;
    stmt = dbConnector->getConnection()->createStatement();
    sql::ResultSet *res = stmt->executeQuery(query);
    
     sql::ResultSetMetaData *metaData = res->getMetaData();
        int columnCount = metaData->getColumnCount();
        std::vector<std::string> columnNames;

        for (int i = 1; i <= columnCount; i++) {
            columnNames.push_back(metaData->getColumnName(i));
        }

        // Print the retrieved data
        int nameWidth = 15;  // Adjust the width as per your needs
        std::cout << std::left;

        // Print the column headers
        for (const std::string& columnName : columnNames) {
            std::cout << std::setw(nameWidth) << columnName << " ";
        }
        std::cout << std::endl;

        // Print the data rows
        while (res->next()) {
            for (const std::string& columnName : columnNames) {
                std::string columnValue = res->getString(columnName);
                std::cout << std::setw(nameWidth) << columnValue << " ";
            }
            std::cout << std::endl;
        }


int value1,ch;
string value2;
string columnvalue;




        while(!updatefalse){
            try {
                cout<<"Enter the batch id you want to update::";
cin>>value1;
cout<<"        Enter the technology you want to update::";
cin>>value2;

cout<<"Accept"<<endl;
cout<<"Reject"<<endl;
cout<<"Enter the choice";
cin>>ch;

if(ch==1){
    columnvalue= "Accepted";
}
else if(ch==2){
    columnvalue="Rejected";
}
string searchQuery= "update allocated_schedules set status = '"+columnvalue+"' where batch_id ="+to_string(value1)+" and technology = '"+value2+"' ";
sql::PreparedStatement *pstmt;
pstmt = dbConnector->getConnection()->prepareStatement(searchQuery);
sql::ResultSet *res1 = pstmt->executeQuery();
updatefalse = true;

    

    std::cout << "Updated successfully." << std::endl;
} catch (sql::SQLException &e) {
   cout<<"Enter the valid details"<<endl;
   cout<<""<<endl;
   cout<<""<<endl;
}
        }

            }       
