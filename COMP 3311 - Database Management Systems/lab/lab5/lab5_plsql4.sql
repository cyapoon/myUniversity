    DECLARE
          i NUMBER(2):=1;
     BEGIN
           FOR R IN (
                   SELECT * FROM facility
           )LOOP
                   UPDATE facility SET no_of_computers= no_of_computers+i WHERE department_id=R.department_id;
                    i:=i+1;
           END LOOP;
      END;