-- In 12.sql, write a SQL query to list the titles of all movies in which both Johnny Depp and Helena Bonham Carter starred.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Johnny Depp.
-- You may assume that there is only one person in the database with the name Helena Bonham Carter.

select m.title
from stars s
JOIN stars s2 ON s.movie_id = s2.movie_id
JOIN people p ON p.id = s.person_id
JOIN people p2 ON p2.id = s2.person_id
INNER JOIN movies m ON s.movie_id = m.id
WHERE p.name = 'Helena Bonham Carter' AND p2.name = 'Johnny Depp';