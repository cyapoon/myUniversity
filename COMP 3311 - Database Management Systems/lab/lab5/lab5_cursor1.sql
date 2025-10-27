DECLARE
 var_deptid facility.department_id%TYPE;
 var_name  facility.name%TYPE;
 CURSOR facility_cursor 
 IS SELECT department_id, name FROM facility; 
BEGIN
 OPEN facility_cursor;
 LOOP
   FETCH facility_cursor INTO var_deptid,var_name;
   EXIT WHEN facility_cursor%NOTFOUND;
   INSERT INTO test VALUES (var_deptid,var_name);
 END LOOP;
 CLOSE facility_cursor;
END;