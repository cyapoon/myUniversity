create unique index facility_idx on facility(department_id, name);

create index function_idx on facility(substr(name,1,8));

select index_name from user_indexes;

create cluster department_facility(department_id varchar2(4));

create table if not EXISTS departments(
    department_id varchar2(4) not null,
    name varchar2(40),
    room_number number(4))
    cluster department_facility(department_id);
    
drop table departments;

DECLARE
    cga_too_low EXCEPTION;
    cga_of_lam NUMBER(2);
begin
    select cga into cga_of_lam from students where email='lamngok';
    if (cga_of_lam < 10) then
        raise cga_too_low;
    end if;
exception
    when cga_too_low then
        dbms_output.put_line('LAM IS LAZY');
        update students set last_name = 'LAZY' where email='lamngok';
end;
/

    