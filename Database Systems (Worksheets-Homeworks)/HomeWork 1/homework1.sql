create database Mall;

use Mall;

create table Customer(
customerId int AUTO_INCREMENT, /* I dont have to write id of customer manually.Its default value is 1 and it increases itself*/
name varchar(10),
lastName varchar(15),
registrationDate date,
primary key(customerId) /* Every id of customer is unique.That's why it is primary key.*/
);

create table Inventory( 
itemId int AUTO_INCREMENT, /* I don't have to write id of item manually.Its default value is 1 and it increases itself */
itemName varchar(20),
cost int,
primary key(itemId) /* Every id of item is unique.That's why it is primary key.*/
);

create table Purchase(
purchaseId int AUTO_INCREMENT, /* I don't have to write id of purchase manually.Its default value is 1 and it increases itself */
itemId int, /*It tell us which item is bought */
customerId int, /* It tell us who bought that item0 */
foreign key(itemId)     references Inventory(itemId),  /* itemId refers to inventory's itemId */
foreign key(customerId) references Customer(customerId), /* customerId refers to customer's customerId */
primary key(purchaseId) /*Every perchase is unique*/
);

/* 5 Diffrent Records */
insert into Customer(name,lastName,registrationDate) values('Kazım','Tulgaroğlu','2020-08-17');
insert into Customer(name,lastName,registrationDate) values('Ali','Özcan','2018-12-15');
insert into Customer(name,lastName,registrationDate) values('Tuğrul','Karay','2019-01-01');
insert into Customer(name,lastName,registrationDate) values('Bora','Kor','2014-08-29');
insert into Customer(name,lastName,registrationDate) values('Selçuk','Çalışkan','2011-05-07');

/* 5 Diffrent Records */
insert into Inventory(itemName,cost) values('Table',35);
insert into Inventory(itemName,cost) values('Refrigerator',750);
insert into Inventory(itemName,cost) values('Laundry Machine',800);
insert into Inventory(itemName,cost) values('Glass',85);
insert into Inventory(itemName,cost) values('Chair',25);

/* 5 Diffrent Records */
insert into Purchase(itemId,CustomerId) values(1,4);
insert into Purchase(itemId,CustomerId) values(2,1);
insert into Purchase(itemId,CustomerId) values(5,2);
insert into Purchase(itemId,CustomerId) values(4,5);
insert into Purchase(itemId,CustomerId) values(3,3);


/* Question 6 */
select customerId from Purchase where Purchase.itemId = 2 ;

/* Question 7 */
alter table Customer add score int ;

/* Question 8 */
update Customer
set score = (year(registrationDate) - 2010)  * 10 ;

/* Question 9 */
select avg((2020 - year(registrationDate))*365 + (10 - month(registrationDate))*30 + (30 - day(registrationDate)))
from Customer 