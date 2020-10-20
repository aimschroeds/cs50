 select avg(rating) AS avg_rating
 from ratings r
 LEFT JOIN movies m ON r.movie_id = m.id
 WHERE m.year = 2012;