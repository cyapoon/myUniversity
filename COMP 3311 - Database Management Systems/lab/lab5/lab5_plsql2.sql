        DECLARE
          room departments.room_number%TYPE;
        BEGIN
          SELECT room_number INTO room FROM departments 
          WHERE department_id='COMP';
          IF (room>3000 and room<4000) THEN
                   UPDATE departments SET room_number=room+2000         
                   WHERE department_id='COMP';
          ELSE
                    UPDATE departments SET room_number=5528 
                    WHERE department_id='COMP';
          END IF;
        END;
