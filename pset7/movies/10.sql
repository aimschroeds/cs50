-- In 10.sql, write a SQL query to list the names of all people who have directed a movie that received a rating of at least 9.0.
-- Your query should output a table with a single column for the name of each person.

select DISTINCT(p.name)
from ratings r
INNER JOIN directors d ON r.movie_id = d.movie_id
INNER JOIN people p ON d.person_id = p.id
WHERE r.rating >= 9.0;