-- In 11.sql, write a SQL query to list the titles of the five highest rated movies (in order) that Chadwick Boseman starred in,
-- starting with the highest rated.
-- Your query should output a table with a single column for the title of each movie.
-- You may assume that there is only one person in the database with the name Chadwick Boseman.

select m.title from people p
INNER JOIN stars s ON p.id = s.person_id AND p.name = 'Chadwick Boseman'
LEFT JOIN movies m ON s.movie_id = m.id
LEFT JOIN ratings r on m.id = r.movie_id
ORDER BY r.rating desc
LIMIT 5;