#include <ostream>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

/* you need to replace the username and password in SQLConnectA() with your own */


int main3(int argc, CHAR* argv[])
{

	HENV   henv;
	HDBC   hdbc;
	HSTMT  hstmt;
	RETCODE retcode;
	SQLINTEGER sqlcode, room;
	SQLLEN room_n;
	SQLSMALLINT len;
	SQLCHAR deptid[50] = "COMP";
	SQLLEN deptid_n = SQL_NTS;

	/* Allocate environment handle */
	retcode = SQLAllocEnv(&henv);

	/* Allocate connection handle */
	retcode = SQLAllocConnect(henv, &hdbc);

	/* Connect to the service */
	/* you need to replace the username and password in SQLConnectA() with your own */
	retcode = SQLConnectA(hdbc, (SQLCHAR*)"comp3311.cse.ust.hk", SQL_NTS, (SQLCHAR*)argv[1], SQL_NTS, (SQLCHAR*)argv[2], SQL_NTS);
	if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO) {
		printf("Connected to Oracle.\n");
	}

	/* execute a SELECT statement*/
	SQLAllocStmt(hdbc, &hstmt);
	retcode = SQLPrepareA(hstmt, (SQLCHAR*)"SELECT room_number FROM departments WHERE department_id=?", SQL_NTS);
	retcode = SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, deptid, 50, &deptid_n);
	retcode = SQLExecute(hstmt);
	retcode = SQLBindCol(hstmt, 1, SQL_C_SLONG, &room, 1, &room_n);


	/* fetch the results into the variable "deptid" and the display*/
	while (TRUE) {
		retcode = SQLFetch(hstmt);
		if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO)
		{
			printf("room = %d\n", room);
		}
		else break;
	}


	/* free resources */
	SQLFreeStmt(hstmt, SQL_CLOSE);
	SQLDisconnect(hdbc);
	SQLFreeConnect(hdbc);
	SQLFreeEnv(henv);

	return 0;

}
