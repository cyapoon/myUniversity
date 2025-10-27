drop trigger chk_email;
drop trigger backup_facility;

drop table math_dept;
drop table students;
drop table courses;
drop table departments;
drop table facility;
drop table old_facility;
drop table testloop;
drop table test;

drop index department_facility_idx;

CREATE TABLE departments
	( department_id	varchar2(4) not null,
		name	varchar2(40),
		room_number	number(4)	);

CREATE TABLE facility
	( department_id	varchar2(4) not null,
	  name	varchar2(40),
      no_of_projectors number(4),
	  no_of_computers  number(5));

create table students
(
	student_id	number(8) not null,
	last_name	varchar2(20),
	first_name	varchar2(25) not null,
	email		varchar2(8) not null,
	phone_number	varchar2(20),
	CGA		number(4,2),
	department_id	varchar2(4) not null,
	admission_date	date);

insert into facility values ('COMP', 'Computer Science', 5, 150);
insert into facility values ('MATH', 'Mathematics',5, 60);
insert into facility values ('ELEC', 'Electronic Engineering', 5, 150);
insert into facility values ('BUS', 'Business',5,110);

insert into departments values ('COMP', 'Computer Science', '3528');
insert into departments values ('MATH', 'Mathematics', '3461');
insert into departments values ('ELEC', 'Electronic Engineering', '2528');
insert into departments values ('BUS', 'Business', '4528');

insert into students values (03456789, 'Porter', 'Harry', 'cs_phx', 23581234, 10.50, 'COMP',to_date('03-SEP-07','DD-MON-YY'));
insert into students values (05456789, 'Da Vinci', 'Leonardo', 'cs_dvl', 23585678, 12.00, 'COMP', to_date('01-SEP-08','DD-MON-YY'));
insert into students values (03456789, 'Greenleaf', 'Legolas', 'ma_glx', 23582468, 9.12, 'MATH',to_date('02-SEP-09','DD-MON-YY'));
insert into students values (04567890, NULL, 'Ceaser', 'ee_cxx', 23589876, 8.34, 'ELEC', to_date('02-SEP-09','DD-MON-YY'));
insert into students values (99987654, 'Lazy', 'Lazy', 'lz_llx', 23581357, 2.55, 'LAZY', to_date('01-SEP-00','DD-MON-YY'));
insert into students values (11567890, 'Lam', 'Alex', 'lamngok', 23589876, 9.00, 'ELEC', to_date('03-SEP-09','DD-MON-YY'));



