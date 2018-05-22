create table parents as
  select "abraham" as parent, "barack" as child union
  select "abraham"          , "clinton"         union
  select "delano"           , "herbert"         union
  select "fillmore"         , "abraham"         union
  select "fillmore"         , "delano"          union
  select "fillmore"         , "grover"          union
  select "eisenhower"       , "fillmore";

create table dogs as
  select "abraham" as name, "long" as fur, 26 as height union
  select "barack"         , "short"      , 52           union
  select "clinton"        , "long"       , 47           union
  select "delano"         , "long"       , 46           union
  select "eisenhower"     , "short"      , 35           union
  select "fillmore"       , "curly"      , 32           union
  select "grover"         , "short"      , 28           union
  select "herbert"        , "curly"      , 31;

create table sizes as
  select "toy" as size, 24 as min, 28 as max union
  select "mini",        28,        35        union
  select "medium",      35,        45        union
  select "standard",    45,        60;

-------------------------------------------------------------
-- PLEASE DO NOT CHANGE ANY SQL STATEMENTS ABOVE THIS LINE --
-------------------------------------------------------------

-- The size of each dog
create table size_of_dogs as
  select dogs.name, sizes.size from dogs, sizes
  where dogs.height > sizes.min and dogs.height <= sizes.max;

-- All dogs with parents ordered by decreasing height of their parent
create table by_height as
  select A.name from dogs as A, dogs as B, parents where
  A.name = parents.child and parents.parent = B.name order by B.height DESC;

-- Sentences about siblings that are the same size
create table sentences as
  with sib as (
  	select A.name as K, B.name as L, C.size as S from dogs as A, dogs as B, sizes as C, sizes as D, parents as E, parents as F
  	where A.height > C.min and A.height <= C.max and B.height > D.min and B.height <= D.max and C.size = D.size and  A.name = E.child and B.name = F.child and E.parent = F.parent and A.name < B.name
  )
  select K || ' and ' || L || ' are ' || S || ' siblings' from sib;


-- Ways to stack 4 dogs to a height of at least 170, ordered by total height
create table stacks as
  select A.name || ', ' || B.name || ', ' || C.name || ', ' || D.name, A.height+B.height+C.height+D.height as H from dogs as A, dogs as B, dogs as C, dogs as D
  where A.height < B.height and B.height < C.height and C.height < D.height and H > 170 order by H ASC;

-- non_parents is an optional, but recommended question
-- All non-parent relations ordered by height difference
create table non_parents as
	with grandparents(grandog, grandpup) as (
      select a.parent, b.child from parents as a, parents as b
        where a.child = b.parent
    ),
    ancestors(ancestor, descendent) as (
      select grandog, grandpup from grandparents union
      select ancestor, child from ancestors, parents
        where parent = descendent
    ),
    relations(first, second) as (
      select ancestor, descendent from ancestors union
      select descendent, ancestor from ancestors
    )
  	select first, second from relations, dogs as f, dogs as s
    where first = f.name and second = s.name order by f.height-s.height;


create table ints as
    with i(n) as (
        select 1 union
        select n+1 from i limit 100
    )
    select n from i;

create table divisors as
    select A.n*B.n as n, count(*) as div
    from ints as A, ints as B
    where A.n*B.n <= 100 
    group by A.n*B.n;

create table primes as
    select n from divisors
    where divisors.div = 2;
