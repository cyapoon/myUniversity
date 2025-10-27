DECLARE
message varchar2(20) := 'Hello World';
begin
dbms_output.put_line(message);
end;
/

set serveroutput on;

DECLARE
    dept_name departments.name%TYPE;
    dept_room departments.room_number%TYPE;
BEGIN
    SELECT name,room_number INTO dept_name, dept_room from departments
    WHERE department_id = 'MATH';
    INSERT INTO math_dept values(dept_name,dept_room);
END;

declare
    room departments.room_number%TYPE;
begin
    select room_number into room from departments
    where department_id = 'COMP';
    if(room>3000 and room<4000) then
        update departments set room_number=room+2000
        where department_id='COMP';
    else
        update departments set room_number=5528
        where department_id = 'COMP';
    end if;
end;

declare
    i testloop.i%TYPE :=1;
begin
    loop
        insert into testloop values(i);
        i:= i+1;
        exit when i>10;
    end loop;
end;

declare
    i number(2):=1;
begin
    for R in(select * from facility) loop
        update facility set no_of_computers=no_of_computers+i
        where department_id = R.department_id;
        i := i+1;
    end loop;
end;

declare
    var_deptid facility.department_id%type;
    var_name facility.name%type;
    CURSOR facility_cursor
    IS SELECT department_id,name from facility;
begin
    OPEN facility_cursor;
    LOOP
        FETCH facility_cursor INTO var_deptid, var_name;
        EXIT WHEN facility_cursor%NOTFOUND;
        INSERT INTO test values(var_deptid,var_name);
    end LOOP;
end;

declare
    var_deptid facility.department_id%type;
    var_name facility.name%type;
    cursor facility_cursor is select department_id,name from facility;
begin
    for rec in facility_cursor loop
        var_deptid := rec.department_id;
        var_name := rec.name;
        insert into test values(var_deptid,var_name);
    end loop;
end;

CREATE OR REPLACE TRIGGER chk_email 
BEFORE INSERT ON students 
FOR EACH ROW
WHEN (NEW.department_id = 'COMP')
declare
    prefix CHAR(3) := 'cs_';
begin
    :NEW.email := prefix || :NEW.email;
end;

insert into students 
values(03454321, 'Rowling', 'Joanne', 'JK', 23781234, 11.50, 'COMP','03-SEP-82', 'COMP197');

create or replace trigger backup_facility
before delete on facility
for each row
declare
    id_null EXCEPTION;
begin
    insert into old_facility values(:old.department_id, :old.name, :old.no_of_projectors, :old.no_of_computers);
EXCEPTION
    when id_null then
        DBMS_OUTPUT.PUT_LINE('Department ID missing');
end;

delete from facility where department_id='MATH';




