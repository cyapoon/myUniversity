/* COMP3311 Lab 7 lab7.sql */

drop table students;
drop table departments;

create table students
(
	student_id	number(8) not null,
	last_name	varchar2(20),
	first_name	varchar2(25) not null,
	email		varchar2(8) not null,
	phone_number	varchar2(20),
	CGA		number(4,2),
	department_id	varchar2(4) not null
);

insert into students values (03456789, 'Lai', 'Rita', 'cs_lrx', 23581234, 10.50, 'COMP');
insert into students values (05678989, 'Yip', 'Marria', 'cs_yma', 23589876, 10.50, 'COMP');
insert into students values (05678901, 'Yip', 'Albert', 'cs_yax', 23585678, 12.00, 'COMP');
insert into students values (06789012, 'Ko', 'Robert', 'ma_krx', 23582468, 9.12, 'MATH');
insert into students values (04567890, NULL, 'Daniel', 'ee_XDx', 23589876, 8.34, 'ELEC');


create table departments
(
	department_id	varchar2(4) not null,
	name	varchar2(40),
	room_number	number(4)	
);

insert into departments values ('COMP', 'Computer Science', '3528');
insert into departments values ('MATH', 'Mathematics', '3461');
insert into departments values ('ELEC', 'Electronic Engineering', '2528');


