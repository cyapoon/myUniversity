/* lab8.sql */

drop table departments;


create table departments
(
	department_id	varchar2(4) not null,
	name	varchar2(40),
	room_number	number(4)	
);


insert into departments values ('COMP', 'Computer Science', '3528');
insert into departments values ('MATH', 'Mathematics', '3461');
insert into departments values ('ELEC', 'Electronic Engineering', '2528');
insert into departments values ('BUS', 'Business', '4528');

