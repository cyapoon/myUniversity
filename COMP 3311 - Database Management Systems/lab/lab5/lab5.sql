Declare
drop_table_stmt varchar2(1000);
Begin
for t in (select table_name from user_tables) loop
drop_table_stmt := 'drop table '||t.table_name||' cascade constraints';
execute immediate drop_table_stmt;
end loop;
end;
/


drop trigger chk_email;
drop trigger backup_facility;

create table math_dept
( name varchar2(40),
  room_number number(4)
);



create table students
(
	student_id	number(8) not null,
	last_name	varchar2(20),
	first_name	varchar2(25) not null,
	email		varchar2(8) not null,
	phone_number	varchar2(20),
	CGA		number(4,2),
	department_id	varchar2(4) not null,
	admission_date	date,
	course_id	varchar2(7)
);

create table courses
(
	course_code	varchar2(7) not null,
	department_id	varchar2(4) not null,
	name	varchar2(40),
	instructor	varchar2(30) not null
);

create table departments
(
	department_id	varchar2(4) not null,
	name	varchar2(40),
	room_number	number(4)	
);

create table facility
( 
  	department_id	varchar2(4) not null,
	name	varchar2(40),
	no_of_projectors number(4),
	no_of_computers  number(5)
);

create table old_facility
( 
  	department_id	varchar2(4) not null,
	name	varchar2(40),
	no_of_projectors number(4),
	no_of_computers  number(5)
);


create table testloop
( 
  i number(4)
);

create table test
( 
  	department_id	varchar2(4) not null,
	name	varchar2(40)
);


insert into students values (03456789, 'Porter', 'Harry', 'cs_phx', 23581234, 10.50, 'COMP','03-SEP-07', 'COMP231');
insert into students values (05456789, 'Da Vinci', 'Leonardo', 'cs_dvl', 23585678, 12.00, 'COMP', '01-SEP-08','COMP231');
insert into students values (03456789, 'Greenleaf', 'Legolas', 'ma_glx', 23582468, 9.12, 'MATH','02-SEP-09', 'ELEC214');
insert into students values (04567890, NULL, 'Ceaser', 'ee_cxx', 23589876, 8.34, 'ELEC', '03-SEP-09','MATH246');
insert into students values (99987654, 'Lazy', 'Lazy', 'lz_llx', 23581357, 2.55, 'LAZY', '01-SEP-00',NULL);



insert into courses values ('COMP231', 'COMP', 'database system', 'Chen Lei');
insert into courses values ('COMP303', 'COMP', 'Web programming', 'David Rossiter');
insert into courses values ('ELEC214', 'ELEC', 'basic electronics theories ', 'Electronic Man');
insert into courses values ('MATH246', 'MATH', 'probability in action', 'Newton');
insert into courses values ('HUMA123', 'HUMA', 'what is a dog', 'Animal');



insert into departments values ('COMP', 'Computer Science', '3528');
insert into departments values ('MATH', 'Mathematics', '3461');
insert into departments values ('ELEC', 'Electronic Engineering', '2528');
insert into departments values ('BUS', 'Business', '4528');

insert into facility values ('COMP', 'Computer Science', 5, 150);
insert into facility values ('MATH', 'Mathematics',5, 60);
insert into facility values ('ELEC', 'Electronic Engineering', 5, 150);
insert into facility values ('BUS', 'Business',5,110);

