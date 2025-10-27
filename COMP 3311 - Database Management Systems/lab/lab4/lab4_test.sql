CREATE TABLE department_facility (
    department_id      VARCHAR2(4) NOT NULL,
    name               VARCHAR2(40),
    no_of_projectors   NUMBER(4),
    no_of_computers    NUMBER(5)
);

RENAME department_facility TO test;

DROP TABLE test;

ALTER TABLE facility ADD (
    funding   NUMBER(10)
);

ALTER TABLE facility MODIFY (
    funding VARCHAR2(10)
);

ALTER TABLE facility DROP ( funding );

INSERT INTO facility (
    department_id,
    name,
    no_of_projectors,
    no_of_computers
) VALUES (
    'COMP',
    'Computer Science',
    5,
    150
);

INSERT INTO facility VALUES (
    'COMP',
    'Computer Science',
    5,
    150
);

INSERT INTO facility ( department_id ) VALUES ( 'test' );

DELETE FROM facility WHERE
    department_id = 'test';

DELETE FROM facility;

--need to insert data back before update!!--
INSERT INTO facility (
    department_id,
    name,
    no_of_projectors,
    no_of_computers
) VALUES (
    'COMP',
    'Computer Science',
    5,
    150
);
--continues

UPDATE facility
    SET
        no_of_computers = 200
WHERE
    department_id = 'COMP';
--Reminder: REFRESH the data--

CREATE TABLE staff (
    id       NUMBER(10) PRIMARY KEY,
    age      NUMBER(3) CHECK (
        age BETWEEN 0 AND 65
    ),
    salary   NUMBER(10) CHECK (
        salary > 0
    )
);
CREATE TABLE work (
    id          NUMBER(10)
        REFERENCES staff ( id ),
    firm_name   VARCHAR2(100) NOT NULL,
    PRIMARY KEY ( id,firm_name )
);

--Create IC with SQL Developer--
--before create IC, drop the previous staff table and create a new one without IC--
drop table work;
CREATE TABLE work (
    id          NUMBER(10),
    firm_name   VARCHAR2(100)
);
--**Try to create IC with SQL Developer here**--
--add table work back--
drop table work;
CREATE TABLE work(
      id number(10), 
      firm_name VARCHAR2(100) 
      CONSTRAINT not_null NOT NULL,
      CONSTRAINT f_key FOREIGN KEY (id) REFERENCES staff (id),  
      CONSTRAINT p_key Primary Key(id, firm_name)
      );
--end of Create IC with SQL Developer--


ALTER TABLE staff ADD CONSTRAINT test
CHECK (age between 20 and 40);

ALTER TABLE work MODIFY (firm_name
null); 

ALTER TABLE staff DROP CONSTRAINT test;

ALTER TABLE work DROP PRIMARY KEY;

ALTER TABLE work MODIFY (PRIMARY KEY (id,firm_name));

SELECT constraint_name FROM user_constraints; 
SELECT * FROM user_constraints; 