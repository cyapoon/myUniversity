DECLARE 
    dept_name departments.name%TYPE;
    dept_room departments.room_number%TYPE;

BEGIN
    SELECT name, room_number INTO dept_name,dept_room FROM departments 
    WHERE department_id='MATH';
    INSERT INTO math_dept values (dept_name,dept_room); 

END;

--*in sql plus, please add a forward slash (/)