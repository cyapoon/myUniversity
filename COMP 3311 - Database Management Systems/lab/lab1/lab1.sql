/* COMP3311 Lab 1 lab1.sql */



drop table students;

create table students
(
	student_id	number(8) not null,
	first_name	varchar2(20),
	last_name	varchar2(25) not null,
	email		varchar2(8) not null,
	phone_number	varchar2(20),
	CGA		number(4,2)
);

insert into students values (03543789, 'Porter', 'Harry', 'cs_phx', 23581234, 10.50);
insert into students values (03456790, 'Da Vinci', 'Leonardo', 'cs_dvl', 23585678, 12.00);
insert into students values (03458372, 'Greenleaf', 'Legolas', 'ma_glx', 23582468, 9.12);


