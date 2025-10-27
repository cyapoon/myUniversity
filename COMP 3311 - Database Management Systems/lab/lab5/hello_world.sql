SET SERVEROUTPUT on;

Declare
message varchar2(20):= 'Hello world!';

Begin
dbms_output.put_line(message);

End;
