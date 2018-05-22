.read fa16data.sql
.read sp17data.sql

CREATE TABLE obedience AS
  select seven, hilfinger from students;

CREATE TABLE smallest_int AS
  select time, smallest from students where smallest > 16 order by smallest ASC limit 20;

CREATE TABLE greatstudents AS
  select A.date, A.color, A.pet, B.number, A.number
  from fa16students as A, students as B
  where A.date = B.date and A.color = B.color and A.pet = B.pet;

CREATE TABLE sevens AS
  select students.seven
  from students, checkboxes
  where students.number = 7 and checkboxes.'7' = 'True' and checkboxes.time = students.time;

CREATE TABLE matchmaker AS
  select A.pet, A.song, A.color, B.color 
  from students as A, students as B
  where A.pet = B.pet and A.song = B.song and A.time < B.time;
