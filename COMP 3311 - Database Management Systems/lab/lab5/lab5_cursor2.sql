DECLARE 
 var_deptid facility.department_id%TYPE;
 var_name  facility.name%TYPE;
 CURSOR facility_cursor 
 IS SELECT department_id, name FROM facility; 
BEGIN
 FOR rec in facility_cursor
  LOOP
   var_deptid:=rec.department_id;
   var_name:=rec.name;
   INSERT INTO test VALUES (var_deptid,var_name); 
  END LOOP;
END;
