select p.name
FROM movies m
INNER JOIN stars s ON m.id = s.movie_id AND m.title = 'Toy Story'
LEFT JOIN people p ON s.person_id = p.id;