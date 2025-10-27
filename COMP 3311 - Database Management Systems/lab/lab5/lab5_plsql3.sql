DECLARE 
	i testloop.i%TYPE :=1;
BEGIN
	LOOP
		INSERT INTO testloop VALUES (i);
		i:=i+1;
		EXIT WHEN i>10;
	END LOOP;
END;