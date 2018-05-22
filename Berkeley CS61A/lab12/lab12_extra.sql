.read lab12.sql

CREATE TABLE fa16favnum AS
  select number, count(*) as count from fa16students 
  group by number order by count DESC
  limit 1;


CREATE TABLE fa16favpets AS
  select pet, count(*) as count from fa16students
  group by pet order by count DESC
  limit 10;


CREATE TABLE sp17favpets AS
  select pet, count(*) as count from students
  group by pet order by count DESC
  limit 10;


CREATE TABLE sp17dragon AS
  select pet, count(*) as count from students
  where pet = 'dragon';


CREATE TABLE sp17alldragons AS
  select pet, count(*) as count from students
  where pet like '%dragon%';


CREATE TABLE obedienceimage AS
  select  seven, hilfinger, count(*) as count from students
  where seven = '7' group by hilfinger;


CREATE TABLE smallest_int_count AS
  select smallest, count(*) from students group by smallest order by smallest ASC;
