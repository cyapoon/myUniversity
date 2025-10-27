CREATE OR REPLACE TRIGGER backup_facility
BEFORE DELETE ON facility
FOR EACH ROW
DECLARE
id_null EXCEPTION;
BEGIN
INSERT INTO old_facility
VALUES (:old.department_id, :old.name, :old.no_of_projectors,
:old.no_of_computers);
EXCEPTION
WHEN id_null THEN
DBMS_OUTPUT.PUT_LINE('Department ID missing');
END;
