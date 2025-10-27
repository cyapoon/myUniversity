CREATE OR REPLACE TRIGGER chk_email
      BEFORE INSERT ON students
FOR EACH ROW
      WHEN (NEW.department_id = 'COMP')
DECLARE
	prefix CHAR(3) := 'cs_';
BEGIN
	:NEW.email := prefix || :NEW.email;
END;
