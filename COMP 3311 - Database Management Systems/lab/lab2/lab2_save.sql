select * from students;

select * from departments;

select department_id, name from departments;

select last_name, CGA, CGA+2 from students;
select last_name, CGA, CGA/2 from students;

select last_name as ln from students;
select CGA/4 as quarter_CGA from students;

select department_id from students;
select distinct department_id from students;

select first_name || last_name as full_name from students;
select last_name || ' studies in ' || department_id from students;

SELECT first_name||' '|| last_name || '(' || student_id || ') ' || 'from the ' || department_id || ' department obtains CGA ' || CGA ||'.' ||' His/Her email is ' || email || '@stu.ust.hk .' AS lab2 FROM students;

select * from departments where department_id = 'COMP';

select * from students where CGA <> 10.5;
select * from students where CGA >= 10.5;
select * from students where CGA <= 10.5;
select * from students where department_id = 'COMP';

select * from students where CGA >10 and department_id = 'MATH';
select * from students where CGA >10 or department_id = 'MATH';
select * from students where department_id not in ('COMP','ELEC');

select * from students where cga between 10 and 12;
select * from students where department_id in ('MATH','ELEC');

SELECT * FROM students WHERE department_id= 'COMP' OR department_id= 'MATH' AND CGA>11;
SELECT * FROM students WHERE (department_id= 'COMP' OR department_id= 'MATH') AND CGA>11;

select * from students order by cga asc;
select * from students order by cga desc;

select first_name, cga*0.8 as wCGA from students order by wCGA;
select * from students order by department_id asc, first_name desc;

select first_name, last_name from students, departments;
select first_name, last_name from students, departments where students.department_id = departments.department_id;

select first_name,department_id, name from students natural join departments;

select first_name, email from students where department_id = 'COMP';
select first_name from students where first_name like '___r%';
select first_name from students where first_name like '%a%' or first_name like '%e%';
select * from students where department_id in ('COMP','ELEC') and (cga <> 8.34 or cga <> 12);



