create table department_facility(
    department_id varchar2(4) not null,
    name varchar2(40),
    no_of_projectors number(4),
    no_of_computers number(5));
    
rename department_facility to test;

drop table test;

alter table facility add (funding number(10));

alter table facility modify (funding varchar2(10));

alter table facility drop (funding);

insert into facility values ('COMP','Computer Science',5,150);

insert into facility (department_id) values('test');

delete from facility where department_id='test';
delete from facility;

update facility set no_of_computers=200 where department_id='COMP';

drop table staff;
drop table work;

create table staff (
    id number(10) primary key,
    age number(3) check (age between 0 and 65),
    salary number(10) check (salary>0));
    
create table work (
    id number(10) references staff(id),
    firm_name varchar2(100) NOT NULL,
    primary key(id,firm_name)
);

create table work(
    id number(10),
    firm_name varchar2(100)
    constraint not_null not null,
    constraint f_key foreign key (id) references staff(id),
    constraint p_key Primary key (id,firm_name)
    );
    
alter table staff add constraint test check (age between 20 and 40);
alter table work modify (firm_name null);

alter table staff drop constraint test;
alter table work drop primary key;
ALTER TABLE work  MODIFY (PRIMARY KEY (id,firm_name));
alter table work add (primary key(id,firm_name));

select constraint_name from user_constraints;