// Use comp3311.cpp instead of this file if you are using lab machine



#include <iostream>
#include <windows.h>
#include <sql.h>
#include <sqlext.h> 
#include <sqltypes.h>
int main02(int argc, char* argv[]) {
    HENV   henv; HDBC   hdbc; HSTMT  hstmt; RETCODE retcode;
    SQLINTEGER sqlcode, deptid_n; SQLSMALLINT len; SQLCHAR deptid[50];

    /* Allocate environment handle */ 
    retcode = SQLAllocEnv(&henv);
    printf("%d", retcode);

    /* Allocate connection handle */
    retcode = SQLAllocConnect(henv, &hdbc);
    printf("%d", retcode);

    /* Connect to the service */ 
    retcode = SQLConnectA(hdbc, (SQLCHAR*)"comp3311.cse.ust.hk", SQL_NTS, (SQLCHAR*)"comp3311stu047", SQL_NTS, (SQLCHAR*)"panjunyuan123", SQL_NTS);
    printf("%d",retcode);
    if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO){
        printf ("Connected to Oracle.\n");
    }

    /* execute a SELECT statement*/ 
    SQLAllocStmt(hdbc, &hstmt); 
    SQLExecDirectA(hstmt, (SQLCHAR*)"select department_ID from departments", SQL_NTS);
    
    /* bind the char string variable "deptid" to get the result from the query*/ 
    SQLBindCol(hstmt, 1, SQL_C_CHAR, deptid, 50, &deptid_n);
    
    /* fetch the results into the variable "deptid" and the display*/
    while (TRUE) { 
        retcode = SQLFetch(hstmt);
        if (retcode == SQL_SUCCESS || retcode == SQL_SUCCESS_WITH_INFO){
            printf("department_id = %s\n", deptid);
        }
        else { 
            break;
        } }

    /* free resources */ 
    SQLFreeStmt(hstmt, SQL_CLOSE); 
    SQLDisconnect(hdbc); 
    SQLFreeConnect(hdbc); 
    SQLFreeEnv(henv);

    return 0;
}

