#include<iostream>
#include<regex>
#include "../headerfiles/admin.h"
#include "../DatabaseConnection/DatabaseConnector.h"
#include <cppconn/prepared_statement.h>
#include <iomanip>
#include <string>
#include<sstream>
using namespace std;

admin::admin(DatabaseConnector* connector) : dbConnector(connector) {}

void admin::startLogin() {
    // Prompt user for name and password
    std::string name, password;
    std::cout << "Enter name: ";
    std::cin >> name;
    std::cout << "Enter password: ";
    std::cin >> password;

    // Perform login
    bool loggedIn = performLogin(name, password);
    // Continue with the program based on login status
    if (loggedIn) {
        //cout<<"logged in"<<endl;
      adminwork();
    } else {
        std::cout << "Invalid name or password. Login failed." << std::endl;
        startLogin();
    }
}

bool admin::performLogin(const std::string& name, const std::string& password) {
    // Query to check if name and password match
    std::string query = "SELECT COUNT(*) FROM admin WHERE name = '" + name + "' AND password = '" + password + "'";

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

void admin::adminwork(){
    //admin work panel
    //each case have different function calling in it according to user input
        int ch;
        cout<<""<<endl;
        cout<<""<<endl;
        cout<<"\t\t\t\t Enter the choice"<<endl;
        cout<<""<<endl;
        cout<<"\t\t\t\t 1:Create a new training Schedule"<<endl;
        cout<<"\t\t\t\t 2:Update the schedule"<<endl;
        cout<<"\t\t\t\t 3:Allocate schedule to a specific trainer"<<endl;
        cout<<"\t\t\t\t 4:Generate the report"<<endl;
        cout<<"\t\t\t\t 5:Quit Application"<<endl;
        cout<<""<<endl;
        cout<<""<<endl;
        cout<<"\t\t\t\t"; cin>>ch;
        switch (ch)
        {
        case 1:
            cout<<"\t\t\t\t create a new training schedule "<<endl;
            create_schedule();
            //adminwork();
            break;
        case 2:
            cout<<"\t\t\t\t Update the schedule"<<endl;
            update_schedule();
            break;
        case 3:
            cout<<"\t\t\t\t Allocate schedule to a specific trainer"<<endl;
            allocate_schedule();
            break;
        case 4:
        cout<<endl;
           
            cout<<endl;
          
           generate_report();
            break;
        case 5:

            cout<<"\t\t\t\t Quit Application"<<endl;
            break;
        default:
                cout<<"\t\t\t\t Invalid choice"<<endl;
                adminwork();
            break;
        }
}

void admin::create_schedule()
{
    string technology, f_details, date1, date2, venue_details, month;
    int batch_id, days;
    cout << "\t\t\t\tEnter batch id::";
        
        cin >> batch_id;
        cout << "\t\t\t\tEnter technology::" ;
       
        cin >> technology;
    //validations for the start date 
       while(true){
            cout<<"\t\t\t\tEnter start Date::";
            cin>>date1;
            if(!regex_match(date1, regex("\\d{2}-\\d{2}-\\d{4}"))){
                cout<<"\t\t\t\t Invalid input. Date must be in the format 'DD-MM-YYYY'.\n";
            }
            else{
                break;
            }
        }

         cout << "\t\t\t\tEnter Number of Days::" ;
       
         cin >> days;
//validations for the end date
        while(true){
            cout<<"\t\t\t\tEnter End Date::";
            cin>>date2;
            if(!regex_match(date2, regex("\\d{2}-\\d{2}-\\d{4}"))){
                cout<<"\t\t\t\tInvalid input. Date must be in the format 'DD-MM-YYYY'.\n";
            }
            else{
                break;
            }
        }
        cout << "\t\t\t\tEnter venue::";
      
        cin >> venue_details;
        cout << "\t\t\t\tEnter month::" ;
        

        cin >> month;
try
{
    cout<<"create the shedule"<<endl;
   
    
std::string query = "insert into shedules(batch_id,technology,venue_details,month,s_date,e_date,days) values('"+to_string(batch_id)+"','"+technology+"','"+venue_details+"','"+month +"','"+date1 +"','"+date2 +"','"+to_string(days) +"');";

sql::PreparedStatement *pstmt;
pstmt = dbConnector->getConnection()->prepareStatement(query);
sql::ResultSet *res = pstmt->executeQuery();

    cout<<"shedule created succesfully";
   
    adminwork();
}
 catch (sql::SQLException &e) {
       std::cout << "SQL Error: " << e.what() << std::endl;
      
    }
}
void admin::update_schedule(){
    bool updatefalse = false;
while(!updatefalse)
{
 std::string query = "select * from shedules";
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
        int nameWidth = 20;  // Adjust the width as per your needs
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

std::string tableName = "shedules";
    std::string column1 = "batch_id";
    std::string column2 = "technology";
    
    int value1;
    string newvalue1;
    cout<<""<<endl;
    cout<<"enter the batch_id::";cin>>value1;
    std::string value2 = "value2";
     cout<<"enter the technology::";cin>>value2;
    string column_name;
    cout<<"Enter the column name u want to update::";cin>>column_name;
    string columnvalue;
    cout<<"Enter the data to upadte::"; cin>>columnvalue;

    std::string searchQuery = "update shedules set "+column_name+" = '"+columnvalue+"'  where batch_id = "+to_string(value1)+" and technology = '"+value2+"' ";
    
       


try {

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
};
void admin::allocate_schedule()
{

       std::string query = "select * from shedules";
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
        int nameWidth = 20;  // Adjust the width as per your needs
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
        cout<<"___________________________________________________________________________________________________________________________________"<<endl;
        cout<<"___________________________________________________________________________________________________________________________________"<<endl;
        
    std::string tableName = "shedules";
    std::string column1 = "batch_id";
    std::string column2 = "technology";

    std::string value1 = "value1";
    cout<<"enter the batch_id::";cin>>value1;
    //getline(cin,value1);
    std::string value2 = "value2";
     cout<<"enter the technology::";cin>>value2;
    std::string searchQuery = "SELECT * FROM " + tableName + " WHERE " + column1 + " = '" + value1 + "' AND " + column2 + " = '" + value2 + "'";

    
       sql::ResultSet *res1 = stmt->executeQuery(searchQuery);
     

        // Check if a row with matching columns was found
        if (res1->next()) {
            // Get the column count and column names
            sql::ResultSetMetaData *metaData = res1->getMetaData();
            int columnCount = metaData->getColumnCount();
            std::vector<std::string> columnNames;

            for (int i = 1; i <= columnCount; i++) {
                columnNames.push_back(metaData->getColumnName(i));
            }

            // Construct the insert query
            std::string newTableName = "allocated_schedules";
            std::string insertQuery = "INSERT INTO " + newTableName + " (";

            // Append the column names to the insert query
            for (const std::string& columnName : columnNames) {
                insertQuery += columnName + ", ";
            }
            // Append the additional user column to the insert query
            std::string userColumnName = "faculty_name";
            
            insertQuery += userColumnName + ") VALUES (";

            // Get the values from the result and append them to the insert query
            for (const std::string& columnName : columnNames)
            {
                std::string columnValue = res1->getString(columnName);
                insertQuery += "'" + columnValue + "', ";
            }
            // Append the user column value to the insert query
            string userColumnValue;
            cout<<"ENter the faculty name::"; 
            //getline(cin,userColumnValue);
            cin>>userColumnValue;
            
            insertQuery += "'" + userColumnValue + "')";

            stmt->execute(insertQuery);

            std::cout << "Data inserted into new table." << std::endl;
            adminwork();
        } else {
            std::cout << "No matching data found." << std::endl;
        }
}
void admin::generate_report()
{
    string technology,month;
    cout<<"Enter the Technology::"; cin>>technology;
    cout<<"Enter the Month::"; cin>>month;
     cout<<"\t\t\t\t *********** REPORT ***********"<<endl;
 std::string query = "select * from shedules where technology='"+technology+"' and month ='"+month+"' ";
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
        int nameWidth = 20;  // Adjust the width as per your needs
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
