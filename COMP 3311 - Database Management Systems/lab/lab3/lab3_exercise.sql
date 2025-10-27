select LOWER(last_name)from students;

select upper(last_name) from students;

select initcap(name) from courses;

select substr(first_name,2,3) from students;

select concat(last_name,first_name) from students;
select last_name||first_name from students;

select instr(last_name, 'or') from students;

select length(last_name) from students;

select lpad('a',10,'b')from students;

select rpad('a',10,'b') from students;

select ltrim('     a  ') from students;

select rtrim('     a  ') from students;

select mod(10,3) from students;
select power(2,10) from students;
select round(3.141592,4) from students;
select trunc(3.141592,4) from students;

select to_date('05-03-14','DD-MM-YY') from dual;
select add_months('05-3月-14',2) from dual;
select last_day('05-3月-14') from dual;
select next_day('05-3月-14','星期六') from dual;

select avg(cga) from students;
select count(cga) from students;
select max(cga) from students;
select min(cga) from students;
select stddev(cga) from students;
select sum(cga) from students;

select department_id, last_name as LN from students group by department_id, last_name;
select department_id, max(cga) from students group by department_id having max(cga)=12 or max(cga) < 10;
select department_id, max(cga) from students where department_id='COMP' group by department_id having max(cga)=12 or max(cga) < 10;

select first_name, department_id, cga from students where cga = (select min(cga) from students);
select department_id, avg(cga) from students group by department_id having avg(cga) > (select avg(cga) from students);

select temp_table.department_id, temp_table.AVG_CGA 
from (select department_id, avg(cga) as AVG_CGA from students group by department_id) temp_table
where temp_table.AVG_CGA > 
(select temp_cga.overall_avg_cga from (select avg(cga) as overall_avg_cga from students)temp_cga);

