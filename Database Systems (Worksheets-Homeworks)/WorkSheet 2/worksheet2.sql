create database University;

use University;

create table Students(
id int,
name varchar(20),
registrationDate date,
gpa float(3,2));

/* Question 3 */
insert into Students values(1, 'Ada',       '2010-01-02',     3.5);
insert into Students values(2, 'Berk',      '2009-10-15',     2.3);
insert into Students values(3, 'Aaron',     '2010-06-18',     2.7);
insert into Students values(4, 'Muhammad',  '2005-08-08',     3.0);
insert into Students values(5, 'Elizabeth', '1999-11-20',     2.2);   

 /* Question 4 */
 select * from students where name like 'A%';  
 
 /* Question 5 */
 select * from Students where registrationDate like '2010%';
 
 /* Question 6 */
 select * from Students where gpa > 2.5;
 
 /* Question 7 */
 alter table Students add phone varchar(11);


/* Question 8 */
update students
set phone = '05212362154'
where name = 'Ada' ;

update students
set phone = '02212861174'
where name = 'Elizabeth' ;

update students
set phone = '07216364154'
where name = 'Berk' ;

update students
set phone = '05312362897'
where name = 'Aaron' ;

update students
set phone = '02312882054'
where name = 'Muhammad' ;    

/* Question 9 */
select stddev(gpa)
from students





