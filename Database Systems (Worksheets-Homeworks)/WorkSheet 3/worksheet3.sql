create database University;

use University;

create table Instructor(
instructorId int,
name varchar(20),
surname varchar(50),
primary key(instructorId)
);

create table Lecture(
lectureId int,
name varchar(50),
department varchar(50),
code int,
instructorId int,
primary key(lectureId),
foreign key(instructorId) references Instructor(instructorId)
);


create table Class(
classId int,
day varchar(10),
hour time,
lectureId int,
primary key(classId),
foreign key(lectureId) references Lecture(lectureId)
);

/*  describe  Instructor  */
/*  describe  Class       */
/*  describe  Lecture     */


insert into Instructor values(1,'Alan','Turing');
insert into Instructor values(2,'Bjarne','Stroustrup');
insert into Instructor values(3,'Dennis','Ritchie');


insert into Lecture values(1,'Database Systems','CMPE',351,1);
insert into Lecture values(2,'Introduction To Programming with C++','CMPE',101,2);
insert into Lecture values(3,'Operating Systems','CMPE',312,3);

insert into Class values(1,'Wednesday','14:00:00',1);
insert into Class values(2,'Tuesday','10:15:00',2);
insert into Class values(3,'Thursday','17:00:00',3);

update Lecture
set instructorId = 3
where instructorId = 1 ;


