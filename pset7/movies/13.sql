-- In 13.sql, write a SQL query to list the names of all people who starred in a movie in which Kevin Bacon also starred.
-- Your query should output a table with a single column for the name of each person.
-- There may be multiple people named Kevin Bacon in the database. Be sure to only select the Kevin Bacon born in 1958.
-- Kevin Bacon himself should not be included in the resulting list.

select DISTINCT(p2.name)
from movies m
JOIN stars s ON m.id = s.movie_id
JOIN stars s2 ON m.id = s2.movie_id AND s2.person_id != s.person_id
LEFT JOIN people p on s.person_id = p.id
LEFT JOIN people p2 on s2.person_id = p2.id
WHERE (p.name = 'Kevin Bacon' AND p.birth = 1958);