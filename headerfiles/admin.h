#include<iostream>
#include <mysql_driver.h>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/statement.h>
#include "../DatabaseConnection/DatabaseConnector.h"
using namespace std;
class admin {
private:
    DatabaseConnector* dbConnector;

public:
    admin(DatabaseConnector* connector);

    void startLogin();
    bool performLogin(const std::string& name, const std::string& password);
    void adminwork();
    void create_schedule();
    void update_schedule();
    void allocate_schedule();
    void generate_report();

};
