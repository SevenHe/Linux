#include <iostream>
using namespace std;

#include <unistd.h>
#include <mysql_connection.h>
#include <mysql_driver.h>
#include <cppconn/driver.h>
#include <cppconn/resultset.h>
#include <cppconn/statement.h>

using namespace sql;

#define HOST "tcp://127.0.0.1:3306/ftp_svr"
#define USER "seven"

int main()
{
	char* pswd;
	pswd = getpass("Your password:");
	Driver* driver;
	Connection* conn;
	driver = get_driver_instance();
	conn = driver->connect(HOST, USER, pswd);
	Statement* stmt = conn->createStatement();
	ResultSet* rs = stmt->executeQuery("SELECT password FROM ftp_user WHERE name = 'seven'");
	if (rs->next()) {
		string ret = rs->getString(1);
		cout << "Get return value: " << ret << endl;
	}
	cout << "Commit Mode: " << conn->getAutoCommit() << endl;
	cout << "Schema: " << conn->getSchema() << endl;
	cout << "Client info: " << conn->getClientInfo() << endl;
	delete conn;
	driver = NULL;
	conn = NULL;
	
	return 0;
}
