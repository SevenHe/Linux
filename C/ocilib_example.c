#include "ocilib.h"

// The ocilib is a external library, so you need to link it when compiling!

int main(int argc, char* argv[])
{
	OCI_Connection* cn;
	OCI_Statement* st;
	OCI_Resultset* rs;

	OCI_Initialize(NULL, NULL, OCI_ENV_DEFAULT);

	cn = OCI_ConnectionCreate("//localhost:1521/XE", "SEVEN", "Seven1001", OCI_SESSION_DEFAULT);
	st = OCI_StatementCreate(cn);

	OCI_ExecuteStmt(st, "select table_name from user_tables");

	rs = OCI_GetResultset(st);

	while(OCI_FetchNext(rs))
	{
		printf("Table : %s\n",OCI_GetString(rs, 1));
	}

	OCI_Cleanup();

	return EXIT_SUCCESS;
}	

