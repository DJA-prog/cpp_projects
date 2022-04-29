#include <stdlib.h>
#include <iostream>
#include <mysql_connection.h>
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace sql;
int main(void){
  sql::Driver *driver;
  sql::Connection *con;

  driver = get_driver_instance();
  con = driver->connect("tcp://127.0.0.1:3306", "i12bretro", "some_very_complex_password");

  return 0;
}