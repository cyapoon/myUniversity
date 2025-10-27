DECLARE 
  	cga_too_low EXCEPTION;
	cga_of_lam  NUMBER(2);
BEGIN
	SELECT cga INTO cga_of_lam 
	FROM students WHERE email='lamngok';
	IF (cga_of_lam<10) THEN
		RAISE cga_too_low;
	END IF;

EXCEPTION 
	WHEN cga_too_low THEN
		DBMS_OUTPUT.PUT_LINE('LAM IS LAZY!');
		UPDATE students SET last_name='LAZY'
		WHERE email='lamngok';
END;
