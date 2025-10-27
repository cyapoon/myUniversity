
#include <ostream>
#include <windows.h>
#include <sql.h>
#include <sqlext.h>
#include <sqltypes.h>

/* The username and password are two variables in SQLConnectA(), which should be given when running the executable */


int main(int argc, CHAR* argv[])
{
      
 HENV   henv;
 HDBC   hdbc;
 HSTMT  hstmt;
 RETCODE retcode;
 SQLINTEGER sqlcode,room_n,room;
 SQLSMALLINT len;
 SQLCHAR deptid[50]="COMP";
 SQLINTEGER deptid_n = SQL_NTS;
 SQLCHAR msg[4000];
 SQLCHAR sqlstate[6];

 /* Allocate environment handle */
  SQLAllocEnv( &henv);

 /* Allocate connection handle */
  SQLAllocConnect(henv, &hdbc);

 /* Connect to the service */
/* The data source name is incorrect in the following statement. So we expect the error message to complain about that */
 retcode = SQLConnectA(hdbc, (SQLCHAR*) "comp1234.cse.ust.hk", SQL_NTS, (SQLCHAR*) argv[1], SQL_NTS, (SQLCHAR*) argv[2], SQL_NTS);
 if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO){
         printf ("Connected to Oracle.\n");}
 else {
	 SQLGetDiagRecA(SQL_HANDLE_DBC,hdbc,1,sqlstate, &sqlcode, msg,4000,&len);
     printf("%s(%s)\n",msg,sqlstate);
     exit(-1); }


/* execute a SELECT statement*/
 SQLAllocStmt(hdbc, &hstmt);
 SQLPrepareA(hstmt, (SQLCHAR*) "SELECT room_number FROM departments WHERE department_id=?", SQL_NTS);
 SQLBindParameter(hstmt, 1, SQL_PARAM_INPUT, SQL_C_CHAR, SQL_CHAR, 0, 0, deptid, 50, &deptid_n);
 SQLExecute(hstmt);
 SQLBindCol(hstmt,1, SQL_C_SLONG,&room,1,&room_n); 

 
/* fetch the results into the variable "deptid" and the display*/
 while (TRUE){
	 retcode=SQLFetch(hstmt);
	 if (retcode==SQL_SUCCESS || retcode ==SQL_SUCCESS_WITH_INFO)
		{printf("room = %d\n",room);}
	 else break;
 }


 /* free resources */
 SQLFreeStmt(hstmt,SQL_CLOSE);
 SQLDisconnect(hdbc);
 SQLFreeConnect(hdbc);
 SQLFreeEnv(henv);

 return 0;

}


