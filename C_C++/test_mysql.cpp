#include <iostream>
using namespace std;

#include <unistd.h>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>

using namespace sql;

#define HOST "tcp://127.0.0.1:3306"
#define USER "seven"

int main()
{
	char* pswd;
	pswd = getpass("Your password:");
	Driver* driver;
	Connection* conn;
	driver = get_driver_instance();
	conn = driver->connect(HOST, USER, pswd);
	cout << "Commit Mode: " << conn->getAutoCommit() << endl;
	cout << "Schema: " << conn->getSchema() << endl;
	cout << "Client info: " << conn->getClientInfo() << endl;
	delete conn;
	driver = NULL;
	conn = NULL;
	
	return 0;
}
