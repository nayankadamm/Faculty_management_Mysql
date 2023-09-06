#include<iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include "../DatabaseConnection/DatabaseConnector.h"
using namespace std;
class faculty{
    private:
    DatabaseConnector* dbConnector;

public:
    faculty(DatabaseConnector* connector);
    void startLogin();
    bool performLogin(const std::string& name, const std::string& password);
    void faculty_work();
    void get_shedule();
    int cancle_shedule();
};