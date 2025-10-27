/* COMP3311 Lab 4 lab4.sql */

drop table students;
drop table courses;
drop table departments;
drop table course_updates;
drop table copy_dept;
drop table facility;

create table students
(
	student_id	number(8) primary key,
	last_name	varchar2(20),
	first_name	varchar2(25) not null,
	email		varchar2(8) not null,
	phone_number	varchar2(20),
	CGA		number(4,2),
	department_id	varchar2(4) not null,
	admission_date	date,
	course_id	varchar2(8)
);

create table courses
(
	course_code	varchar2(8) primary key,
	department_id	varchar2(4) not null,
	name	varchar2(40),
	instructor	varchar2(30) not null
);

create table departments
(
	department_id	varchar2(4) primary key,
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

create table copy_dept
(
	department_id	varchar2(4) primary key,
	name	varchar2(40),
	room_number	number(4)	
);

create table course_updates
(
	course_code	varchar2(8) primary key,
	department_id	varchar2(4) not null,
	name	varchar2(40),
	instructor	varchar2(30) not null
);

insert into students values (11456789, 'Porter', 'Harry', 'cs_phx', 23581234, 10.50, 'COMP','01-SEP-11', 'COMP3311');
insert into students values (11456709, 'Da Vinci', 'Leonardo', 'cs_dvl', 23585678, 12.00, 'COMP', '01-SEP-11','COMP3311');
insert into students values (09456789, 'Greenleaf', 'Legolas', 'ma_glx', 23582468, 9.12, 'MATH','03-SEP-09', 'ELEC214');
insert into students values (09567890, NULL, 'Ceaser', 'ee_cxx', 23589876, 8.34, 'ELEC', '03-SEP-09','MATH246');
insert into students values (08987654, 'Lazy', 'Lazy', 'lz_llx', 23581357, 2.55, 'LAZY', '01-SEP-08',NULL);



insert into courses values ('COMP3311', 'COMP', 'Database System', 'Lei Chen');
insert into courses values ('COMP1004', 'COMP', 'C++ Programming', 'Brian Mak');
insert into courses values ('ELEC214', 'ELEC', 'Electronics', 'Electronic Man');
insert into courses values ('MATH246', 'MATH', 'Probability', 'Newton');
insert into courses values ('HUMA123', 'HUMA', 'What is Human', 'Animal');


insert into course_updates values ('HUMA1234', 'HUMA', 'What is Human', 'Prof. Blue');
insert into course_updates values ('COMP9999', 'COMP', 'Individual Project', 'Prof. White');


insert into departments values ('COMP', 'Computer Science', '3528');
insert into departments values ('MATH', 'Mathematics', '3461');
insert into departments values ('ELEC', 'Electronic Engineering', '2528');
insert into departments values ('LANG', 'Language', '5434');

insert into facility values ('COMP', 'Computer Science', 5, 150);
insert into facility values ('MATH', 'Mathematics',5, 30);
insert into facility values ('ELEC', 'Electronic Engineering', 5, 150);
insert into facility values ('BUS', 'Business',5,30);

insert into copy_dept values ('COMP', 'Computer Science', NULL);
insert into copy_dept values ('MATH', NULL, NULL);


